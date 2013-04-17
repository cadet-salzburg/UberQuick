#ifndef ITEM_H
#define ITEM_H
#include <QObject>
#include <QPoint>
#include <QSize>

namespace Uber {

    class Item : public QObject
    {
        Q_OBJECT
        Q_PROPERTY ( QString className READ getClassName )
        Q_PROPERTY( QPointF position READ getPosition WRITE setPosition NOTIFY positionChanged )
        Q_PROPERTY( float x READ x WRITE setX NOTIFY positionChanged )
        Q_PROPERTY( float y READ y WRITE setY NOTIFY positionChanged )
        Q_PROPERTY( QSizeF size READ size WRITE setSize )
    public:
        Item(QObject *parent = nullptr );
        Item(QObject *parent, QPointF position, QSizeF size);
        Item(const Item &other);

        QPointF                 getPosition() const;
        float                   x() const;
        float                   y() const;

        QSizeF                  size() const;
        void                    setSize(const QSizeF &size);
        Q_INVOKABLE QString     getClassName() const
        {
            return QString( metaObject()->className());
        }

    protected:

    private:
        QPointF                 m_Position;
        QSizeF                  m_Size;
        int                     m_Orientation;
    signals:
        void                    positionChanged();
    public slots:

        void                    setPosition(const QPointF &position );
        void                    setX( float x );
        void                    setY( float y );

    };
}
#endif // ITEM_H
