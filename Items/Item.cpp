#include "Item.h"
#include <QDebug>
namespace Uber {
    Item::Item(QObject *parent)
        :QObject(parent)
        ,m_Position( QPointF())
        ,m_Size(100,50)
        ,m_Orientation(Qt::Horizontal)
    {

    }
    Item::Item(QObject *parent, QPointF position, QSizeF size )
        :QObject(parent)
        ,m_Position(position)
        ,m_Size(size)
        ,m_Orientation(Qt::Horizontal)
    {

    }
    Item::Item(const Item &other)
        :QObject(other.parent())
        ,m_Position(other.getPosition())
        ,m_Size(other.size())
        ,m_Orientation(Qt::Horizontal)
    {

    }

    float  Item::x() const
    {
        return m_Position.x();
    }

    float Item::y() const
    {
        return m_Position.y();
    }

    void Item::setX( float x )
    {
        if ( m_Position.x() != x )
        {
            //qDebug() << "position Was changed";
            m_Position.setX(x);
            emit positionChanged();
        }
    }

    void Item::setY( float y )
    {
        if ( m_Position.y() != y )
        {
            //qDebug() << "position Was changed";
            m_Position.setY(y);
            emit positionChanged();
        }
    }

    QPointF Item::getPosition() const
    {
        return m_Position;
    }
    void Item::setPosition(const QPointF &position)
    {
        //qDebug() << "position Was changed";
        m_Position = position;
    }
    QSizeF Item::size() const
    {
        return m_Size;
    }
    void Item::setSize(const QSizeF &size)
    {
        m_Size = size;
    }
}
