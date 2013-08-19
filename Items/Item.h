#ifndef ITEM_H
#define ITEM_H
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QUrl>
#include <QDebug>

namespace Uber {
    class Item : public QObject
    {
        Q_OBJECT
        Q_PROPERTY ( QString className READ getClassName CONSTANT )
        Q_PROPERTY( QPointF position READ getPosition WRITE setPosition NOTIFY positionChanged )
        Q_PROPERTY( float x READ x WRITE setX NOTIFY xChanged )
        Q_PROPERTY( float y READ y WRITE setY NOTIFY yChanged )
        Q_PROPERTY( QSizeF size READ size WRITE setSize )
    public:
        Item(QObject *parent = nullptr );
        Item(QObject *parent, QPointF position, QSizeF size);
        Item(const Item &other);
        virtual ~Item();

        Q_INVOKABLE QPointF     getPosition() const;
        float                   x() const;
        float                   y() const;

        QSizeF                  size() const;
        void                    setSize(const QSizeF &size);

        QString                 getClassName() const
        {

            return m_Classname;
        }


        virtual void            connectSignals(){}
        virtual void            disconnectSignals(){}

    protected:
        QString                 m_Classname;
    private:
        QPointF                 m_Position;
        QSizeF                  m_Size;
    signals:
        void                    killSelf();
        void                    positionChanged(QPointF);
        void                    positionChanged();
        void                    xChanged(float);
        void                    yChanged(float);
        void                    urlChanged();

    public slots:
        void                    setPosition(const QPointF &position );
        void                    setX( float x );
        void                    setY( float y );
        void                    remove();
    };
}
#endif // ITEM_H
