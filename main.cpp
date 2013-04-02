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
#include "Models/BlockObjectListModel.h"
#include "Models/QObjectListModel.h"
#include "QmlLine.h"


using namespace Uber;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
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
    system->getQmlEngine()->rootContext()->setContextProperty("DockView", dock );
    qmlRegisterType<Uber::Item>();
    qmlRegisterType<Uber::Block>();
    qmlRegisterType<BlockObjectListModel>();
    qmlRegisterType<QObjectListModel>();
    qmlRegisterType<Uber::QmlLine>("UberComponents", 0, 1, "Line");

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

    //QObject::connect( system->getQmlEngine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
//    QObject::connect(system->getGraphModel(), SIGNAL(countChanged()),
//                     canvas, SLOT(update()));


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
    int res =  app.exec();
    return res;
}
