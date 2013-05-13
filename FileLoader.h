#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>

namespace Uber
{

    class System;

    class FileLoader : public QObject
    {

     Q_OBJECT

    public:

        FileLoader( System &system, QObject *parent = nullptr );
        FileLoader( FileLoader const& other );
        FileLoader& operator=( FileLoader const& other );
        ~FileLoader();


        //Q_INVOKABLE void loadFile( Uber::System *sys, QString const& filename );

        Q_INVOKABLE void loadFile( QString const& filename );

    private:

        static const QString sFrameworkSuffix;
        static const QString sUbercodeSuffix;

        System &mSystem;

    };
}

#endif // FILELOADER_H
