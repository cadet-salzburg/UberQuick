#include "FileLoader.h"

#include <QtWidgets\QFileDialog>

#include <iostream>

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
    std::cout << "FileLoader::loadFile called, " << filename.toStdString() << std::endl;
}
