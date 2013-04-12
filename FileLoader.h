#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QException>

class FileLoader : public QObject
{

    Q_OBJECT

public:

    class LoadException : public QException
    {
    public:
        LoadException( QString const& msg );
    private:
        QString     mMessage;
    };

    FileLoader( QObject *parent = nullptr );
    FileLoader( FileLoader const& other );
    FileLoader& operator=( FileLoader const& other );
    ~FileLoader();

    Q_INVOKABLE void loadFile( QString const& filename );

private:

};

#endif // FILELOADER_H
