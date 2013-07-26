#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "system/System.h"
#include "_2RealDatatypes.h"
#include "_2RealApplication.h"
#include <memory>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    qRegisterMetaType<CustomTypeRef>("CustomTypeRef");
    Uber::System *system = Uber::System::getInstance();
    system->loadBundles();
    system->loadInterfaceBlocks();
    system->registerQmlTypes();
    system->setContextProperties();
    system->loadQmlFiles();
    system->enableTransparentWindows();
    system->showWindows();
    int res =  app.exec();
    delete system;
    return res;
}
