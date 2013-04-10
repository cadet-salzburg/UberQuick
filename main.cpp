#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "System.h"


using namespace Uber;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    System *system = System::getInstance();
    system->loadBundles();
    system->registerQmlTypes();
    system->setContextProperties();
    system->loadQmlFiles();
    system->enableTransparentWindows();
    system->showWindows();

    int res =  app.exec();
    delete system;
    return res;
}
