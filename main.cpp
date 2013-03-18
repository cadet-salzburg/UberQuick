#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickView>
#include <QQuickItem>
#include <QDebug>
#include <dwmapi.h>
#include "System.h"
#include "Models/DockModel.h"
#include "Items/Block.h"
#include "Items/Outlet.h"
#include "Items/Inlet.h"
#include <iostream>
#include <string>
#include "Models/DataflowModel.h"
#include "Items/ComplexDelegate.h"

using namespace Uber;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //qmlRegisterType<UbConnection>("UberCode",1,0,"UberConnection");

//    QQmlEngine engine;
//    QQmlContext *objectContext = new  QQmlContext(engine.rootContext());

//    QQmlComponent component(&engine, QUrl::fromLocalFile("qml/Dock/Dock.qml") );
//    QObject *myObject = component.create();
//    QQuickItem *item  = qobject_cast<QQuickItem*>(myObject);

//    QQuickWindow *mainW = new QQuickWindow();
//    item->setParent(mainW);
//    mainW->show();


    System *system = System::getInstance();
    system->loadBundles();

    QAbstractItemModel *dockModel = system->getDockModel();
    DataflowModel *dataflowModel = new DataflowModel();

    //------------Custom Delegate Test Starts ----------------------//
    //qmlRegisterType<IntervalSettings>( "UberQuick", 1, 0, "ComplexDelegate");


    Block *m_block = new Block();
    Inlet *m_inlet = new Inlet();
    dataflowModel->addEntry(m_block);
    dataflowModel->addEntry(m_inlet);
    system->getQmlEngine()->rootContext()->setContextProperty( "_flowmodel", dataflowModel );
    ComplexDelegate *complexDelegate(new ComplexDelegate());
    //QUrl url = QUrl
    complexDelegate->addDelegate(QString(m_block->getClassName()),QUrl::fromLocalFile("qml/Workbench/Block.qml"));
    complexDelegate->addDelegate(QString(m_inlet->getClassName()),QUrl::fromLocalFile("qml/Workbench/Inlet.qml"));
    system->getQmlEngine()->rootContext()->setContextProperty( "_complexDelegate", complexDelegate );
    //------------Custom Delegate Test Ends ----------------------//
    //QQmlEngine *engine = new QQmlEngine;

    QQuickView *canvas = new QQuickView( system->getQmlEngine(), 0);
    canvas->setResizeMode(QQuickView::SizeRootObjectToView);
    canvas->setGeometry(300,200, 640, 480);
    canvas->show();



    QQuickView *dock = new QQuickView(system->getQmlEngine(), 0);
    dock->setResizeMode(QQuickView::SizeRootObjectToView);
    dock->setGeometry(300,200, 400, 150);
    dock->show();

    system->getQmlEngine()->rootContext()->setContextProperty( "_model", dockModel );
    system->getQmlEngine()->rootContext()->setContextProperty("_dockView", dock );

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setAlphaBufferSize(8);
    surfaceFormat.setRenderableType(QSurfaceFormat::OpenGLES);
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

    QObject::connect( system->getQmlEngine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
    //MS-Win code to enable transparent OpenGL windows.
    HWND hWndA = (HWND)dock->winId();
    HWND hWndB = (HWND)canvas->winId();
    DWM_BLURBEHIND bb = {0};
    HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.hRgnBlur = hRgn;
    bb.fEnable = TRUE;
    DwmEnableBlurBehindWindow(hWndA, &bb);
    DwmEnableBlurBehindWindow(hWndB, &bb);
    Uber::Item item;
    Uber::Block blockA, blockB;
    Uber::Inlet inlet;
    Uber::Outlet outlet;
//    std::string s("Hello");
//    std::cout << "_Ba: " << typeid(s).name() << std::endl;
//    std::cout << "_Item: " << std::string( item.getClassName().toUtf8().constData() ) << std::endl;
//    std::cout << "_Ba: " << std::string( blockA.getClassName().toUtf8().constData() ) << std::endl;
//    std::cout << "_Bb: " << std::string( blockB.getClassName().toUtf8().constData() ) << std::endl;
//    std::cout << "_Inlet: " << std::string( inlet.getClassName().toUtf8().constData() ) << std::endl;
//    std::cout << "_Outlet: " << std::string( outlet.getClassName().toUtf8().constData() ) << std::endl;
//    Uber::Item *bl = new Uber::Block;
//    std::cout << "_Ba: " << std::string( bl->getClassName().toUtf8().constData() ) << std::endl;
    return app.exec();
}
