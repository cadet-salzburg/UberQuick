#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>

namespace Uber
{

    // TODO: move to sep. file, this is just a placeholder for now

    class System;

    class FileLoader : public QObject
    {

     Q_OBJECT

    public:

        FileLoader( System &system, QObject *parent = nullptr );
        FileLoader( FileLoader const& other );
        FileLoader& operator=( FileLoader const& other );
        ~FileLoader();

        /*
        *   this is called from qml on loading a file
        */
        Q_INVOKABLE void loadFile( QString const& filename );

    private:

        static const QString sFrameworkSuffix;
        static const QString sUbercodeSuffix;

        System &mSystem;

    };
}

#endif // FILELOADER_H
