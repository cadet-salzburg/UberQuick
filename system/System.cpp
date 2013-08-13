#include <memory>
#include <dwmapi.h>
#include <QDir>
#include <QDebug>
#include <QQmlEngine>
#include <QStringList>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQmlContext>
#include <QStringListModel>
#include <iostream>
#include <QQmlEngine>
#include <QQuickView>

#include "../system/System.h"
#include "../system/FileLoader.h"
#include "../system/ConnectionManager.h"
#include "../system/ComplexDelegate.h"
#include "../models/DockModel.h"
#include "../models/ItemObjectListModel.h"
#include "../models/DockModel.h"
#include "../models/InletObjectListModel.h"
#include "../models/OutletObjectListModel.h"
#include "../models/ItemObjectListModel.h"
#include "../models/StringModel.h"
#include "../items/Item.h"
#include "../items/BaseInlet.h"
#include "../items/BaseOutlet.h"
#include "../items/FrameworkBlock.h"
#include "../qml_extensions/Canvas.h"
#include "../qml_extensions/Circle.h"
#include "../qml_extensions/BezierCurve.h"
#include "../qml_extensions/PainterBezier.h"
#include "../items/Link.h"
#include "../ui_items/SliderBlock.h"
#include "../ui_items/TextIO.h"
#include "../qml_extensions/PixelView.h"
#include "../ui_items/Image.h"

using namespace _2Real;
using namespace _2Real::app;

namespace Uber {
    System* System::m_Instance = nullptr;
    System::System()
    :QObject(nullptr)
    ,m_DockModel(nullptr)
    ,m_ComplexDelegate(nullptr )
    ,m_ItemModel(nullptr)
    ,m_2RealEngine( Engine::instance())
    ,m_QmlEngine(nullptr)
    ,m_DockWindow(nullptr)
    ,m_CanvasWindow(nullptr)
    ,m_FileLoader( nullptr )
    ,m_ConnectionManager(nullptr)
    {
        m_DockModel =       new DockModel(0);
        m_ComplexDelegate = new ComplexDelegate(0);
        m_ItemModel =       new ItemObjectListModel(0);
        m_QmlEngine =    new QQmlEngine(0);

        m_FileLoader = new FileLoader( *this );
        m_ConnectionManager = new ConnectionManager(m_ItemModel);



        registerQmlTypes();
        setComplexDelegates();


        qRegisterMetaType< std::shared_ptr<const _2Real::CustomType> >("std::shared_ptr<const _2Real::CustomType>");
    }

    System::~System()
    {
        qDebug() << "Destructor called";

    }

    void System::createWindows()
    {
        m_DockWindow =   new QQuickView( m_QmlEngine, 0 );
        m_CanvasWindow = new QQuickView( m_QmlEngine, 0 );
        QSurfaceFormat  surfaceFormat;
        surfaceFormat.setAlphaBufferSize(8);
        surfaceFormat.setStencilBufferSize(8);
        m_CanvasWindow->setResizeMode(QQuickView::SizeRootObjectToView);
        m_CanvasWindow->setGeometry(300,200, 640, 480);
        m_CanvasWindow->setFormat( surfaceFormat );
        m_CanvasWindow->setClearBeforeRendering(true);
//        QObject::connect(m_CanvasWindow, SIGNAL(focusObjectChanged(QObject *)),this, SLOT(changedFocus(QObject *)));
//        QObject::connect(m_CanvasWindow, SIGNAL(destroyed()), this, SLOT(cleanup()));

        m_DockWindow->setResizeMode(QQuickView::SizeRootObjectToView);
        m_DockWindow->setGeometry(300,200, 400, 150);
        m_DockWindow->setFormat(m_SurfaceFormat);
        m_DockWindow->setClearBeforeRendering(true);
        m_DockWindow->setColor(Qt::transparent);
        m_DockWindow->setFlags(Qt::SplashScreen );//| Qt::FramelessWindowHint );
        //m_DockWindow->setAttribute(Qt::WA_TranslucentBackground);
    }

    void System::registerQmlTypes()
    {
        qmlRegisterType<SliderBlock>();
        qmlRegisterType<BaseInlet>();
        qmlRegisterType<BaseOutlet>();
        qmlRegisterType<InletObjectListModel>();
        qmlRegisterType<OutletObjectListModel>();

        qmlRegisterType<FrameworkBlock>();

        qmlRegisterInterface<Item>("Item");
        qmlRegisterInterface<StringModel>("StringModel");

        qmlRegisterType<Link>();
        qmlRegisterType<TextIO>();
        qmlRegisterType<Image>();

        qmlRegisterType<QStringListModel>();
        qmlRegisterType<QAbstractItemModel>();
        qmlRegisterType<ItemObjectListModel>();
        qmlRegisterType<Canvas>("UberComponents", 1,0,"GraphCanvas");
        qmlRegisterType<Circle>("UberComponents", 1,0,"Circle");
        qmlRegisterType<PainterBezier>("UberComponents", 1,0,"Bezier");
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
        m_QmlEngine->rootContext()->setContextProperty( "DockView", m_DockWindow );
        m_QmlEngine->rootContext()->setContextProperty( "Canvas", m_CanvasWindow );
        m_QmlEngine->rootContext()->setContextProperty( "ItemModel", m_ItemModel );
        m_QmlEngine->rootContext()->setContextProperty( "cpFileLoader", m_FileLoader );
    }

    void System::enableTransparentWindows()
    {
        //MS-Win specific code to enable transparent windows.
        HWND hWndA = (HWND)m_DockWindow->winId();
        HWND hWndB = (HWND)m_CanvasWindow->winId();
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
        m_CanvasWindow->show();
        //m_DockWindow->show();
    }

    void System::removeItem(Item *item)
    {
        if ( item )
        {
            int idx = m_ItemModel->indexOf(item);
            if ( idx!=-1)
            {
                delete item;
                m_ItemModel->removeAt(idx);
            }
        }
    }

    void System::loadQmlFiles()
    {
        m_CanvasWindow->setSource(QUrl::fromLocalFile("qml/Windows/MainWindow.qml"));
        m_DockWindow->setSource(QUrl::fromLocalFile("qml/Windows/Dock.qml"));

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
                        BundleHandle bundleHandle = m_2RealEngine.loadBundle(file.toStdString());
                        BundleMetainfo bundleInfo = bundleHandle.getBundleMetainfo();
                        std::vector< BlockMetainfo > blocks;
                        bundleInfo.getExportedBlocks(blocks);

                        std::vector< BlockMetainfo >::const_iterator iter = blocks.begin();
                        for ( ; iter!= blocks.end(); ++iter )
                        {
                            if( !iter->isContext() )		// don't show or use context blocks in ubercode
                            {
                                GridEntry entry;
                                QString blockName = QString::fromStdString( iter->getName() );
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
        slider.setName("SliderBlock");
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
        m_ComplexDelegate->addDelegate(QString("Uber::FrameworkBlock"),QUrl::fromLocalFile("qml/Canvas/UberBlock.qml"));
        m_ComplexDelegate->addDelegate(QString("Uber::Link"), QUrl::fromLocalFile("qml/Canvas/Link.qml"));
        m_ComplexDelegate->addDelegate(QString("Uber::SliderBlock"),QUrl::fromLocalFile("qml/Canvas/SliderBlock.qml"));
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
        QPointF dockPosition = m_DockWindow->position();
        QPointF dotPosition  = dockPosition + QPointF(m_DockWindow->width()/2 - 75, -15);
        QPointF inputPosition = dotPosition - m_CanvasWindow->position();
        return inputPosition;
    }

    QQuickView *System::getWindow() const
    {
        return m_CanvasWindow;
    }


    void System::addDockItem( int index )
    {
        Item* item = m_DockModel->create( index );
        if ( item )
        {
            item->setPosition( getDockInputPosition() );
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
            //leftovers = m_2RealEngine.loadConfig( config );
            //ConfigLoader loader( this, config );

            //m_2RealEngine.loadConfiguration( dataSource.toStdString() );
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
        if ( m_CanvasWindow->isActive() )
        {
            m_DockWindow->hide();
        }
    }

    void System::cleanup()
    {
        delete m_DockModel;
        delete m_ItemModel;
        delete m_QmlEngine;
        delete m_ComplexDelegate;
        delete m_CanvasWindow;
        delete m_DockWindow;
    }
}
