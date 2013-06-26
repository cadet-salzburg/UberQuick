#include <QtWidgets/QApplication>
#include <QFrame>
#include <QPushButton>
#include "qtquick2applicationviewer.h"
#include "system/System.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Uber::System *system = Uber::System::getInstance();
    system->loadBundles();
    system->loadInterfaceBlocks();
    system->registerQmlTypes();
    system->setContextProperties();
    system->loadQmlFiles();
    system->enableTransparentWindows();
    system->showWindows();
    //
    // Main window
//     QWidget *window = new QWidget( NULL, Qt::FramelessWindowHint );
//     window->setAttribute( Qt::WA_TranslucentBackground );
//     window->setAttribute( Qt::WA_DeleteOnClose );
//     window->setFixedSize( 500, 300 );

//     // Inner frame
//     QFrame *frame = new QFrame( window );
//     frame->move( 10, 10 );
//     frame->setFixedSize( 480, 280 );

//     // Button
//     QPushButton *button = new QPushButton( frame );
//     button->setText( "Minimize" );
//     button->move( 20, 20 );
//     button->setFixedSize( 120, 40 );

//     QObject::connect( button, SIGNAL( clicked() ), window, SLOT( showMinimized() ) );

//     window->show();
     //

    int res =  app.exec();
    delete system;
    return res;
}
