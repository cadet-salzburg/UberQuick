<<<<<<< HEAD
=======
#include <QtGui/QGuiApplication>
>>>>>>> 0d3503c935bac1044a9fec8fca400f7e9b58bc73
#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "System.h"

<<<<<<< HEAD
=======
#include "FileLoader.h"

using namespace Uber;

void registerQmlTypes()
{
    qmlRegisterType<Inlet>();
    qmlRegisterType<Outlet>();
    qmlRegisterType<InletObjectListModel>();
    qmlRegisterType<OutletObjectListModel>();


    qmlRegisterType< FileLoader >( "LogicComponents", 1, 0, "FileLoader" );

    //    qmlRegisterType<Item>();
    //    qmlRegisterType<Block>();
    //    qmlRegisterType<BlockObjectListModel>();

    //    qmlRegisterType<OutletObjectListModel>();
    //    qmlRegisterType<QObjectListModel>();
    //    qmlRegisterType<BlockObjectListModel>();

    //    qmlRegisterType<Block>();
    //    qmlRegisterType<Inlet>();
         //qmlRegisterType<QCppItem,1>("MyModule", 1, 1, "CppItem")
    //    qmlRegisterType<Uber::QmlLine>("UberComponents", 0, 1, "Line");
>>>>>>> 0d3503c935bac1044a9fec8fca400f7e9b58bc73

using namespace Uber;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

<<<<<<< HEAD
    System *system = System::getInstance();
    system->loadBundles();
    system->registerQmlTypes();
    system->setContextProperties();
    system->loadQmlFiles();
    system->enableTransparentWindows();
    system->showWindows();
=======
    registerQmlTypes();
    QApplication app(argc, argv);
    System *system = System::getInstance();
    system->loadBundles();
    QAbstractItemModel *dockModel = system->getDockModel();


    QQuickView *canvas = new QQuickView( system->getQmlEngine(), 0);
    canvas->setResizeMode(QQuickView::SizeRootObjectToView);
    canvas->setGeometry(300,200, 640, 480);
    canvas->show();

    QQuickView *dock = new QQuickView(system->getQmlEngine(), 0);
    dock->setResizeMode(QQuickView::SizeRootObjectToView);
    dock->setGeometry(300,200, 400, 150);
    dock->show();

    system->getQmlEngine()->rootContext()->setContextProperty( "DockModel", dockModel );
    system->getQmlEngine()->rootContext()->setContextProperty( "DockView", dock );

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setAlphaBufferSize(8);
    //surfaceFormat.setRenderableType(QSurfaceFormat::OpenGLES);
    dock->setFormat(surfaceFormat);
    dock->setClearBeforeRendering(true);
    dock->setColor(Qt::transparent);
    dock->setSource(QUrl::fromLocalFile("qml/Dock/Dock.qml"));
    dock->setFlags(Qt::Window | Qt::FramelessWindowHint);

    canvas->setFormat(surfaceFormat);
    canvas->setClearBeforeRendering(true);
    //canvas->setColor(Qt::transparent);
    canvas->setSource(QUrl::fromLocalFile("qml/Workbench/MainWindow.qml"));
    //view->setFlags(Qt::Window | Qt::FramelessWindowHint);

    //QObject::connect( system->getQmlEngine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
//    QObject::connect(system->getGraphModel(), SIGNAL(countChanged()),
//                     canvas, SLOT(update()));

>>>>>>> 0d3503c935bac1044a9fec8fca400f7e9b58bc73

    int res =  app.exec();
    delete system;
    return res;
}
