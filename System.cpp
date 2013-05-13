#include <QDir>
#include <QDebug>
#include <QQmlEngine>
#include <QStringList>
#include <QQuickWindow>
#include <QQmlContext>
#include <dwmapi.h>
#include "Items/Item.h"
#include "Items/Inlet.h"
#include "Items/Outlet.h"
#include "Items/Block.h"
#include "Models/DockModel.h"
#include "Models/InletObjectListModel.h"
#include "Models/OutletObjectListModel.h"
#include "Models/ItemObjectListModel.h"
#include "FileLoader.h"
#include "System.h"

using namespace _2Real;
using namespace _2Real::app;

namespace Uber {
    System* System::m_Instance = nullptr;
    System::System()
    :QObject(nullptr)
    ,m_DockModel(new DockModel())
    ,m_ItemModel(new ItemObjectListModel())
    ,m_Engine(Engine::instance())
    ,m_QmlEngine(new QQmlEngine )
    ,m_Canvas(new QQuickView( m_QmlEngine, 0))
    ,m_Dock(new QQuickView( m_QmlEngine, 0))
    , mFileLoader( new FileLoader( *this ) )
    {
        m_SurfaceFormat.setAlphaBufferSize(8);
        m_Canvas->setResizeMode(QQuickView::SizeRootObjectToView);
        m_Canvas->setGeometry(300,200, 640, 480);
        m_Canvas->setFormat(m_SurfaceFormat);
        m_Canvas->setClearBeforeRendering(true);

        m_Dock->setResizeMode(QQuickView::SizeRootObjectToView);
        m_Dock->setGeometry(300,200, 400, 150);
        m_Dock->setFormat(m_SurfaceFormat);
        m_Dock->setClearBeforeRendering(true);
        m_Dock->setColor(Qt::transparent);
        m_Dock->setFlags(Qt::Window | Qt::FramelessWindowHint);

        registerQmlTypes();
    }

    System::~System()
    {
        delete m_DockModel;
        delete m_ItemModel;
        delete m_QmlEngine;
        delete m_ComplexDelegate;
        delete m_Canvas;
        delete m_Dock;
    }

    void System::registerQmlTypes()
    {
        qmlRegisterType<Inlet>();
        qmlRegisterType<Outlet>();
        qmlRegisterType<InletObjectListModel>();
        qmlRegisterType<OutletObjectListModel>();
        qmlRegisterType<Block>();
        qmlRegisterType<Item>();
        qmlRegisterType<ItemObjectListModel>();

        // fileloader now has no default ctor any more, and thus cannot be registered
        //qmlRegisterType< FileLoader >( "LogicComponents", 1, 0, "FileLoader" );

        // singleton thingie
        //qmlRegisterSingletonType< System >( "LogicComponents", 1, 0, "SystemSingleton", blargh );
        //qmlRegisterType< System >();
    }

    void System::setContextProperties()
    {
        m_QmlEngine->rootContext()->setContextProperty( "DockModel", m_DockModel );
        m_QmlEngine->rootContext()->setContextProperty( "DockView", m_Dock );
        m_QmlEngine->rootContext()->setContextProperty( "Canvas", m_Canvas );
        m_QmlEngine->rootContext()->setContextProperty( "System", this );
        m_QmlEngine->rootContext()->setContextProperty( "cpFileLoader", mFileLoader );
    }

    void System::enableTransparentWindows()
    {
        //MS-Win specific code to enable transparent windows.
        HWND hWndA = (HWND)m_Dock->winId();
        HWND hWndB = (HWND)m_Canvas->winId();
        DWM_BLURBEHIND bb = {0};
        HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.hRgnBlur = hRgn;
        bb.fEnable = TRUE;
        DwmEnableBlurBehindWindow(hWndA, &bb);
        DwmEnableBlurBehindWindow(hWndB, &bb);
    }

    void System::showWindows()
    {
        m_Canvas->show();
        m_Dock->show();
    }

    void System::loadQmlFiles()
    {
        m_Canvas->setSource(QUrl::fromLocalFile("qml/Workbench/MainWindow.qml"));
        m_Dock->setSource(QUrl::fromLocalFile("qml/Dock/Dock.qml"));
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
        m_QmlEngine->rootContext()->setContextProperty( "ItemModel", m_ItemModel );
    }

    DockModel* System::getDockModel()
    {
        return m_DockModel;
    }

    ItemObjectListModel*   System::getItemModel()
    {
        return m_ItemModel;
    }

    QPointF System::maptoGlobal( QQuickItem *item )
    {
        QQuickWindow *win = item->window();
        QPointF itemRootPos = item->mapToScene(QPoint(item->x(), item->y()));
        QPointF winPos(win->x(), win->y());
        return winPos+itemRootPos;
    }

    QPointF System::getDockInputPosition()
    {
        QPointF dockPosition = m_Dock->position();
        QPointF dotPosition  = dockPosition + QPointF(m_Dock->width()/2 - 75, -15);
        QPointF inputPosition = dotPosition - m_Canvas->position();
        return inputPosition;
    }

    void System::addBlock( int index )
    {
        //int row = index.row();
        GridEntry entry = m_DockModel->getEntry(index);
        BlockHandle handle = entry.getBundleHandle().createBlockInstance(entry.getBlockName().toUtf8().constData());
        Block* block = new Block( handle );
        block->setPosition(getDockInputPosition());

        block->setName(entry.getBlockName());
        m_ItemModel->append(block);
    }

    void System::loadConfig( QString const& dataSource )
    {
        try
        {
            // TODO: rewrite the framework's loading routine

            //UberConfig leftovers;
            //leftovers = m_Engine.loadConfig( config );
            //ConfigLoader loader( this, config );

            m_Engine.loadConfiguration( dataSource.toStdString() );
        }
        catch ( _2Real::XMLFormatException &e )
        {
            std::cout << e.what() << std::endl;
            // the framework failed to load; but ubercode has not
            // yet done anything. in this case, cleaning up is the frameworks' responsibility

            // also, not sure if xmlformat is the only possible exception
            // have to check the fw code for that
        }
        catch ( std::exception & e )
        {
            std::cout << e.what() << std::endl;
        }
        catch ( ... )
        {
            // the framework did its part, but ubercode failed
            // this likely means something is very wrong, so shutdown?
        }
    }
}
