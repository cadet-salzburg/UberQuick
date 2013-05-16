#include "Link.h"
namespace Uber {
    Link::Link()
    :m_Inlet( nullptr )
    ,m_Outlet( nullptr )
    {

    }
    void Link::setInlet( Inlet *inlet )
    {
        m_Inlet = inlet;
        QObject::connect(inlet, SIGNAL(positionChanged()),this, SLOT(setValue(int)));
    }

    void Link::setOutlet( Outlet *outlet )
    {
        m_Outlet = outlet;
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
        if ( m_Inlet && m_Outlet )
        {
            return m_Inlet->getPosition();
        } else
        {
            return m_EndPos;
        }
    }

    void Link::updateEndPosition( const QPointF& point )
    {
        m_EndPos = point;
    }
    QDebug operator<<(QDebug dbg, const Link &link )
    {
        dbg.nospace() << "Link";
        return dbg.maybeSpace();
    }
}
