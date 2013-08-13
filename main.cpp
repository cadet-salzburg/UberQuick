#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "system/System.h"
#include "_2RealDatatypes.h"
#include "_2RealApplication.h"
//#include "vld.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qRegisterMetaType<CustomTypeRef>("CustomTypeRef");
    Uber::System *system = Uber::System::getInstance();
    //QObject::connect(system->getWindow(), SIGNAL(clicked()), qApp, SLOT(quit()));
    system->loadBundles();
    system->loadInterfaceBlocks();
    system->registerQmlTypes();
    system->setContextProperties();
    system->loadQmlFiles();
    system->enableTransparentWindows();
    system->showWindows();
    int res =  app.exec();
    delete system;
    //qApp->quit();
    return res;
}
