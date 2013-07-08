#ifndef STRINGOBJECT_H
#define STRINGOBJECT_H

#include <QObject>
#include <QString>
namespace Uber {
    class StringObject : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString string READ getString WRITE setString NOTIFY stringChanged FINAL )
    public:
        StringObject(QObject *parent = 0);
        Q_INVOKABLE QString     getString();
        void        setString( const QString& string );
    private:
        QString m_String;
    signals:
        void stringChanged();
    public slots:
    };
}
#endif // STRINGOBJECT_H
