#include "Item.h"

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
        ,m_Position(other.position())
        ,m_Size(other.size())
        ,m_Orientation(Qt::Horizontal)
    {

    }

    QPointF Item::position() const
    {
        return m_Position;
    }
    void Item::setPosition(const QPointF &position)
    {
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
