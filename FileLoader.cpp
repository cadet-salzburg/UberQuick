#include "FileLoader.h"
#include "System.h"

#include <QtWidgets\QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QUrl>
#include <QFileInfo>

#include <iostream>

namespace Uber
{
    const QString FileLoader::sFrameworkSuffix = QString( "fbef" );
    const QString FileLoader::sUbercodeSuffix = QString( "ubef" );

    FileLoader::FileLoader( System &system, QObject *parent ) :
        QObject( parent )
      , mSystem( system )
    {
    }

    FileLoader::FileLoader( FileLoader const& other ) :
        QObject( other.parent() )
      , mSystem( other.mSystem )
    {
    }

    FileLoader& FileLoader::operator=( FileLoader const& other )
    {
        if ( this == &other )
            return *this;

        return *this;
    }

    FileLoader::~FileLoader()
    {
    }

    void FileLoader::loadFile( QString const& filename )
    {
        // TODO: probably want to perform all sorts of file checks

        QUrl url( filename );
        QString path = url.path();

        std::cout << path.toStdString() << std::endl;

        QFileInfo info( filename );
        std::cout << info.baseName().toStdString() << std::endl;
        std::cout << info.suffix().toStdString() << std::endl;
        std::cout << info.absoluteFilePath().toStdString() << std::endl;

        if ( info.suffix() == sUbercodeSuffix )
        {
            // the framework now has to load & create stuff
            //class FrameworkConfig;
            //class UberCodeConfig : public FrameworkConfig;

            //UbercodeConfig config;
            //framework->loadConfig( file, config );

            // now i need to handle all the ubercode specific stuff, i.e. positioning etc
            //loader->loadConfig( file, config );

            // now this needs to be added to the model, yay
            //System->addConfig( config );
        }
        else if ( info.suffix() == sFrameworkSuffix )
        {
            // the framework now has to load & create stuff
            //FrameworkConfig config = framework->loadFile();

            // now the ub specific info needs to be added

            // and now this needs to be added to the model, yay
        }
        else
        {
            std::cout << "whatever you're trying to load here is not a ubercode OR framework file. you suck." << std::endl;
            return;
        }

        // also: i'm stupid so I'll have to remove the file:/// manually
        QString tmp = filename;
        tmp.remove( 0, 8 );
        //std::cout << "FileLoader::loadFile called, " << tmp.toStdString() << std::endl;
        QFile file( tmp );
        file.open( QIODevice::ReadOnly );

        if ( !file.isOpen() )
        {
            std::cout << "could not open your shitty file, fuck you" << std::endl;
            return;
        }
        else
            std::cout << "congrats, you fucker, your file is open & I'll read it now" << std::endl;

        QByteArray byteData = file.readAll();

        QDataStream printy;
        printy << byteData;
        std::cout << byteData.length() << std::endl;

        file.close();
    }

}
