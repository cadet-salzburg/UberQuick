#include "Link.h"
#include <QDebug>

namespace Uber {
    Link::Link(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Inlet(nullptr)
    ,m_Outlet(nullptr)
    {

    }

    Link::Link(Inlet *inlet, Outlet *outlet, QQuickItem *parent )
    :QQuickItem(parent)
    ,m_Inlet(inlet)
    ,m_Outlet(outlet)
    {

    }

    Link::Link(const Link &other)
    :QQuickItem(other.parentItem())
    ,m_Inlet(other.getInlet())
    ,m_Outlet(other.getOutlet())
    {

    }

    Inlet*  Link::getInlet() const
    {
        return m_Inlet;
    }

    void Link::setInlet(Inlet *const inlet)
    {
        m_Inlet = inlet;
    }

    Outlet* Link::getOutlet() const
    {
        return m_Outlet;
    }

    void Link::setOutlet(Outlet *const outlet)
    {
        m_Outlet = outlet;
    }

    QPointF Link::getStart() const
    {
        //This returns a reference
        return m_LinkNodes.front();
    }

    void Link::setStart( QPointF start )
    {
        m_LinkNodes.front() = start;
    }

    QPointF Link::getEnd() const
    {
        //This returns a reference
        return m_LinkNodes.back();
    }

    void Link::setEnd( QPointF end )
    {
        m_LinkNodes.back() = end;
    }

    void Link::link()
    {
        m_Inlet->getInletHandle().link(m_Outlet->getOutletHandle());
    }

    void Link::unlink()
    {
        m_Inlet->getInletHandle().unlinkFrom(m_Outlet->getOutletHandle());
    }

    QSGNode* Link::updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData )
    {
        Q_UNUSED( updatePaintNodeData)
        return nullptr;
    }
    void Link::updateLinkNodes()
    {
        qDebug() << "Link::updateLinkNodes() was called.";
    }
}
