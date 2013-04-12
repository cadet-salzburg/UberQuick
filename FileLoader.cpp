#include "FileLoader.h"

#include <QtWidgets\QFileDialog>
#include <QFile>
#include <QByteArray>

#include <iostream>

FileLoader::LoadException::LoadException( QString const& msg ) :
    QException()
    , mMessage( msg )
{
}

FileLoader::FileLoader( QObject *parent ) : QObject( parent )
{
}

FileLoader::FileLoader( FileLoader const& other ) : QObject( other.parent() )
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
