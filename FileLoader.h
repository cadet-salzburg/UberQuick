#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>

class FileLoader : public QObject
{

    Q_OBJECT

public:

    FileLoader( QObject *parent = nullptr );
    FileLoader( FileLoader const& other );
    FileLoader& operator=( FileLoader const& other );
    ~FileLoader();

    Q_INVOKABLE void loadFile( QString const& filename );

private:

};

#endif // FILELOADER_H
