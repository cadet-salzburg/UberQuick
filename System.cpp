#include <QDir>
#include <QDebug>
#include <QQmlEngine>
#include <QStringList>
#include <QQuickWindow>
#include <QQmlContext>
#include "Items/Block.h"
#include "System.h"
#include "Models/DockModel.h"

using namespace _2Real;
using namespace _2Real::app;

namespace Uber {
    System* System::m_Instance = nullptr;
    System::System()
    :QObject(nullptr)
    ,m_DockModel(nullptr)
    ,m_BlockModel(new BlockObjectListModel(0))
    ,m_Engine(Engine::instance())
    ,m_QmlEngine(new QQmlEngine )
    {

    }

    System::~System()
    {
        qDebug() << "destructor called";
    }

    void System::loadBundles()
    {
        QDir searchDir("blocks");
        searchDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        QStringList bundleSearchFolders = searchDir.entryList();

        QStringList nameFilters;
        nameFilters << "*.dll" << "*.DLL" << "*.so" << "*.a" << "*.sl" << "*.dylib" << "*.bundle" ;
        //QStringList bundlePaths;
        GridEntryList entries;

        for ( QStringList::iterator iter = bundleSearchFolders.begin(); iter!=bundleSearchFolders.end(); ++iter )
        {
            QString path = searchDir.filePath(*iter);
            QDir bundleDir(path);

            QFileInfoList fileInfoList = bundleDir.entryInfoList( nameFilters, QDir::Files | QDir::Readable );
            for ( QFileInfoList::const_iterator fileInfoIter = fileInfoList.constBegin(); fileInfoIter != fileInfoList.constEnd(); ++fileInfoIter )
            {
                try
                {
                    QString path = fileInfoIter->canonicalPath();
                    QString filename = fileInfoIter->fileName();
                    QString delim("_32");
                    QStringList fileNameParts = filename.split(delim);
                    if (!fileNameParts.empty())
                    {
                        QString file = path + QString("/") + *(fileNameParts.begin());
                        BundleHandle bundleHandle = m_Engine.loadBundle(file.toStdString());
                        BundleInfo bundleInfo = bundleHandle.getBundleInfo();
                        BundleInfo::BlockInfos blocks = bundleInfo.exportedBlocks;

                        BundleInfo::BlockInfos::const_iterator iter = blocks.begin();
                        for ( ; iter!= blocks.end(); ++iter )
                        {
                            QString blockName = QString::fromStdString( iter->name );
                            if( blockName != "contextblock")		// don't show or use context blocks in ubercode
                            {
                                GridEntry entry;
                                entry.setBlockName(blockName);
                                entry.setBundleHandle(bundleHandle);
                                QFile file(bundleDir.filePath("icon.png"));
                                if ( file.exists() )
                                {
                                    QString iconPath = path + QString("/") + QString("icon.png");
                                    entry.setIconUrl(QUrl::fromLocalFile(iconPath));
                                }
                                entries << entry;
                            }
                        }
                    }
                }
                catch ( NotFoundException& e)
                {
                    //std::cout << e.what() << " " << e.message() << std::endl;
                }
                catch ( AlreadyExistsException& e)
                {
                    //std::cout << e.what()  << " " << e.message() << std::endl;
                }
                catch ( ... )
                {
                    //std::cout << "Other exception" << std::endl;
                }
            }
        }

        m_DockModel = new DockModel();
        m_DockModel->addEntries(entries);
        m_ComplexDelegate = new ComplexDelegate();
        m_ComplexDelegate->addDelegate(QString("Uber::Block"),QUrl::fromLocalFile("qml/Workbench/Block.qml"));
        m_QmlEngine->rootContext()->setContextProperty( "ComplexDelegate", m_ComplexDelegate );
        m_QmlEngine->rootContext()->setContextProperty("System", this );
        m_QmlEngine->rootContext()->setContextProperty( "BlockModel", m_BlockModel );
    }

    DockModel* System::getDockModel()
    {
        return m_DockModel;
    }

    BlockObjectListModel*   System::getBlockModel()
    {
        return m_BlockModel;
    }

    QPointF System::maptoGlobal(QQuickItem *item)
    {
        QQuickWindow *win = item->window();
        QPointF itemRootPos = item->mapToScene(QPoint(item->x(), item->y()));
        QPointF winPos(win->x(), win->y());
        return winPos+itemRootPos;
    }

    void System::addBlock( int index, QPoint pos )
    {
        //int row = index.row();
        GridEntry entry = m_DockModel->getEntry(index);
        BlockHandle handle = entry.getBundleHandle().createBlockInstance(entry.getBlockName().toUtf8().constData());
        Block* block = new Block( handle );
        block->setPosition(pos);

        block->setName(entry.getBlockName());
        m_BlockModel->append(block);
    }
}
