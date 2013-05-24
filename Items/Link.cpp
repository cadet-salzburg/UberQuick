#include "Link.h"
namespace Uber {
    Point::Point(QPointF p)
    :QObject(nullptr)
    ,m_Point(p)
    {

    }

    QPointF Point::get() const
    {
        return m_Point;
    }

    void Point::set( const QPointF &p )
    {
        m_Point = p;
    }

    qreal Point::getX() const
    {
        return m_Point.x();
    }

    void Point::setX( const qreal &x )
    {
        m_Point.setX(x);
    }

    qreal Point::getY() const
    {
        return m_Point.y();
    }

    void Point::setY( const qreal &y )
    {
        m_Point.setY(y);
    }

    Link::Link()
    :m_Inlet( nullptr )
    ,m_Outlet( nullptr )
    {

    }
    void Link::setInlet( Inlet *inlet )
    {
        m_Inlet = inlet;
        QObject::connect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
    }

    void Link::setOutlet( Outlet *outlet )
    {
        m_Outlet = outlet;
        QObject::connect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
    }

    void Link::addPoint( const QPointF &p )
    {
        m_Points.push_back(new Point(p) );
    }

    QObjectList Link::getPoints()
    {
        return m_Points;
    }

    QPointF Link::getStartPos()
    {
        if ( m_Outlet )
        {
            return m_Outlet->getPosition();
        } else if ( m_Inlet )
        {
            return m_Inlet->getPosition();
        } else
        {
            return QPointF(0,0);
        }
    }

    QPointF Link::getEndPos()
    {
        QPointF pos(0,0);
        if ( m_Inlet && m_Outlet )
        {
            pos =  m_Inlet->getPosition();
        } else
        {
            if ( m_Points.back() )
            {
                Point* last = qobject_cast<Point*>(m_Points.back());
                pos = last->get();
            }
        }
        return pos;
    }

    void Link::updateEndPosition( const QPointF& point )
    {
        if ( m_Points.back() )
        {
            Point* last = qobject_cast<Point*>(m_Points.back());
            last->set(point);
        }
    }

    QDebug operator<<(QDebug dbg, const Link &link )
    {
        dbg.nospace() << "Link";
        return dbg.maybeSpace();
    }
}
