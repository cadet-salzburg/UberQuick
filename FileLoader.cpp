#include "FileLoader.h"
#include "System.h"

#include <QtWidgets\QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QUrl>
#include <QFileInfo>
#include <QtCore>

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

        // check the suffix to see if this is even a valid file before opening
        if ( !( info.suffix() == sUbercodeSuffix || info.suffix() == sFrameworkSuffix ) )
        {
            std::cout << "whatever you're trying to load here is not a ubercode OR framework file. you suck." << std::endl;
            return;
        }

        // also: i'm stupid so I'll have to remove the 'file:///' manually
        QString tmp = filename;
        tmp.remove( 0, 8 );
        QFile file( tmp );
        file.open( QIODevice::ReadOnly );

        //std::ifstream stream;
        //stream.open( ( QFileToifstream( file ) );

        if ( !file.isOpen() )
        {
            std::cout << "could not open your shitty file, " << tmp.toStdString() << ", so fuck you" << std::endl;
            return;
        }
        else
            std::cout << "congrats, you fucker, your file " << tmp.toStdString() << " is open & I'll read it now" << std::endl;

        //QByteArray byteData = file.readAll();
        //QDataStream printy;
        //printy << byteData;
        //std::cout << byteData.length() << std::endl;

        QTextStream text( &file );
        QString string = text.readAll();

        //UberConfig config( string );
        //file.close();

        mSystem.loadConfig( string );

        //std::cout << string.toStdString() << std::endl;

        //if ( info.suffix() == sUbercodeSuffix )
        //{
            // create a config out of the file...
            //UberConfig config;
            //file.close();

            // let the system handle the rest

            // framework: handles whatever it handles
            // should it return not handled parts? or do we assu

            //mSystem.loadConfig( config );
        //}
        //else /* must be a framework file then */
        //{
            //UberConfig config;
            //file.close();

            //mSystem.loadConfig( config );

            // the framework now has to load & create stuff
            //FrameworkConfig config = framework->loadFile();

            // now the ub specific info needs to be added

            // and now this needs to be added to the model, yay
        //}
    }

    //UberConfig::UberConfig( QString const& string )
    //{

    //}
}
