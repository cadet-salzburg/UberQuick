#include <QDir>
#include <QDebug>
#include <QQmlEngine>
#include <QStringList>
#include <QQuickWindow>
#include <QQmlContext>
#include <dwmapi.h>
#include "../items/Item.h"
#include "../items/Inlet.h"
#include "../items/Outlet.h"
#include "../items/Block.h"
#include "../items/Canvas.h"
#include "../items/Circle.h"
#include "../items/BezierCurve.h"
#include "../items/Link.h"
#include "../items/Slider.h"
#include "../items/TextIO.h"
#include "../items/PixelView.h"
#include "../items/Image.h"
#include "../models/DockModel.h"
#include "../models/InletObjectListModel.h"
#include "../models/OutletObjectListModel.h"
#include "../models/ItemObjectListModel.h"
#include "../system/FileLoader.h"
#include "../system/System.h"
#include "../system/EventFilter.h"
#include "../system/ConnectionManager.h"
#include "../system/ComplexDelegate.h"
#include "../models/StringModel.h"
#include <QStringListModel>
#include <memory>

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
using namespace _2Real;
using namespace _2Real::app;

namespace Uber {
    System* System::m_Instance = nullptr;
    System::System()
    :QObject(nullptr)
    ,m_DockModel(new DockModel())
    ,m_ComplexDelegate( new ComplexDelegate() )
    ,m_ItemModel(new ItemObjectListModel())
    ,m_Engine(Engine::instance())
    ,m_QmlEngine(new QQmlEngine )
    ,m_Dock(new QQuickView( m_QmlEngine, 0))
    ,m_Canvas(new QQuickView( m_QmlEngine, 0))
    , mFileLoader( new FileLoader( *this ) )
    ,m_CurrentLink(nullptr)
    ,m_ConnectionManager(nullptr)
    {
        m_SurfaceFormat.setAlphaBufferSize(8);
        m_SurfaceFormat.setStencilBufferSize(8);
        m_Canvas->setResizeMode(QQuickView::SizeRootObjectToView);
        m_Canvas->setGeometry(300,200, 640, 480);
        m_Canvas->setFormat(m_SurfaceFormat);
        m_Canvas->setClearBeforeRendering(true);
        QObject::connect(m_Canvas, SIGNAL(focusObjectChanged(QObject *)),this, SLOT(changedFocus(QObject *)));
        QObject::connect(m_Canvas, SIGNAL(destroyed()), this, SLOT(cleanup()));

        m_Dock->setResizeMode(QQuickView::SizeRootObjectToView);
        m_Dock->setGeometry(300,200, 400, 150);
        m_Dock->setFormat(m_SurfaceFormat);
        m_Dock->setClearBeforeRendering(true);
        m_Dock->setColor(Qt::transparent);
        m_Dock->setFlags(Qt::SplashScreen );//| Qt::FramelessWindowHint );
        //m_Dock->setAttribute(Qt::WA_TranslucentBackground);

        registerQmlTypes();
        setComplexDelegates();

        m_ConnectionManager = new ConnectionManager(m_ItemModel);
        qRegisterMetaType< std::shared_ptr<const _2Real::CustomType> >("std::shared_ptr<const _2Real::CustomType>");
    }

    System::~System()
    {
        qDebug() << "Destructor called";
        delete m_DockModel;
        delete m_ItemModel;
        delete m_QmlEngine;
        delete m_ComplexDelegate;
        delete m_Canvas;
        delete m_Dock;
    }

    void System::registerQmlTypes()
    {
        qmlRegisterType<Slider>();
        qmlRegisterType<Inlet>();
        qmlRegisterType<Outlet>();
        qmlRegisterType<InletObjectListModel>();
        qmlRegisterType<OutletObjectListModel>();
        qmlRegisterType<QSortFilterProxyModel>();
        qmlRegisterType<Block>();
        qmlRegisterType<Item>();
        qmlRegisterType<Link>();
        qmlRegisterType<Slider>();
        qmlRegisterType<TextIO>();
        qmlRegisterType<Image>();
        qmlRegisterType<StringModel>();
        qmlRegisterType<QStringListModel>();
        qmlRegisterType<QAbstractItemModel>();
        qmlRegisterType<ItemObjectListModel>();
        qmlRegisterType<Canvas>("UberComponents", 1,0,"GraphCanvas");
        qmlRegisterType<Circle>("UberComponents", 1,0,"Circle");
        qmlRegisterType<BezierCurve>("UberComponents", 1,0,"Bezier");
        qmlRegisterType<EventFilter>("UberComponents", 1, 0, "MouseFilter");
        qmlRegisterType<PixelView>("UberComponents", 1, 0, "ImageView");

        //fileloader now has no default ctor any more, and thus cannot be registered
        //qmlRegisterType< FileLoader >( "LogicComponents", 1, 0, "FileLoader" );

        // singleton thingie
        //qmlRegisterSingletonType< System >( "LogicComponents", 1, 0, "SystemSingleton", blargh );
        //qmlRegisterType< System >();
    }

    void System::setContextProperties()
    {
        m_QmlEngine->rootContext()->setContextProperty( "System", this );
        m_QmlEngine->rootContext()->setContextProperty( "DockModel", m_DockModel );
        m_QmlEngine->rootContext()->setContextProperty( "ComplexDelegate", m_ComplexDelegate );
        m_QmlEngine->rootContext()->setContextProperty( "ConnectionManager",m_ConnectionManager );
        m_QmlEngine->rootContext()->setContextProperty( "DockView", m_Dock );
        m_QmlEngine->rootContext()->setContextProperty( "Canvas", m_Canvas );
        m_QmlEngine->rootContext()->setContextProperty( "ItemModel", m_ItemModel );
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
        //m_Dock->show();
    }

    void System::loadQmlFiles()
    {
        m_Canvas->setSource(QUrl::fromLocalFile("qml/Windows/MainWindow.qml"));
        m_Dock->setSource(QUrl::fromLocalFile("qml/Windows/Dock.qml"));

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
//                    qDebug() << path;
                    QString filename = fileInfoIter->fileName();
                    QString delim("_32");
                    QStringList fileNameParts = filename.split(delim);
                    if (!fileNameParts.empty())
                    {
                        std::cout << "LOADING " << fileNameParts.front().toStdString() << std::endl;
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
                                entry.setName(blockName);
                                entry.setBundleHandle(bundleHandle);
                                QFile file(bundleDir.filePath("icon.png"));
                                if ( file.exists() )
                                {
                                    QString iconPath = path + QString("/") + QString("icon.png");
                                    qDebug() << "Icon path: " << iconPath;
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
        m_DockModel->addEntries(entries);
    }

    void System::loadInterfaceBlocks()
    {
        GridEntry slider = GridEntry(SliderType);
        QString sliderIconPath("qrc:///images/slider-icon.png");
        slider.setIconUrl(QUrl(sliderIconPath));
        slider.setName("Slider");
        m_DockModel->addEntry(slider);
        //
        GridEntry textInput = GridEntry(TextInputType);
        QString textInputIconPath("qrc:///images/textedit-icon.png");
        textInput.setIconUrl(QUrl(textInputIconPath));
        textInput.setName("TextInput");
        m_DockModel->addEntry(textInput);
        //
        GridEntry imageOutput = GridEntry(ImageType);
        QString imageOutputIconPath("qrc:///images/image-icon.png");
        imageOutput.setIconUrl(QUrl(imageOutputIconPath));
        imageOutput.setName("Image");
        m_DockModel->addEntry(imageOutput);
    }

    void System::setComplexDelegates()
    {
        m_ComplexDelegate->addDelegate(QString("Uber::Block"),QUrl::fromLocalFile("qml/Canvas/UberBlock.qml"));
        m_ComplexDelegate->addDelegate(QString("Uber::Link"), QUrl::fromLocalFile("qml/Canvas/Link.qml"));
        m_ComplexDelegate->addDelegate(QString("Uber::Slider"),QUrl::fromLocalFile("qml/Canvas/SliderBlock.qml"));
        m_ComplexDelegate->addDelegate(QString("Uber::TextIO"),QUrl::fromLocalFile("qml/Canvas/TextBlock.qml"));
        m_ComplexDelegate->addDelegate(QString("Uber::Image"),QUrl::fromLocalFile("qml/Canvas/ImageBlock.qml"));
    }

    DockModel* System::getDockModel()
    {
        return m_DockModel;
    }

    ItemObjectListModel*   System::getItemModel()
    {
        return m_ItemModel;
    }

    ConnectionManager *System::getConnectionManager()
    {
        return m_ConnectionManager;
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

    QQuickView *System::getWindow() const
    {
        return m_Canvas;
    }


    void System::addDockItem( int index )
    {
        Item* item = m_DockModel->create( index );
        if ( item )
        {
            item->setPosition( getDockInputPosition() );
            item->setUrl(m_ComplexDelegate->getDelegate(item->getClassName()));
             m_ItemModel->append(item);
        }
        qDebug() << "Number of items: " << m_ItemModel->count();
    }

    void System::loadConfig( QString const& dataSource )
    {
        try
        {
            // TODO: rewrite the framework's loading routine

            //UberConfig leftovers;
            //leftovers = m_Engine.loadConfig( config );
            //ConfigLoader loader( this, config );

            //m_Engine.loadConfiguration( dataSource.toStdString() );
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

    void System::changedFocus(QObject *focusObject)
    {
        Q_UNUSED(focusObject)
        if ( m_Canvas->isActive() )
        {
            m_Dock->hide();
        }
    }

}
