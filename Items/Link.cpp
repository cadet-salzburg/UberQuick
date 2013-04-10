#include "Link.h"

namespace Uber {
    Link::Link(QObject *parent)
    :Item(parent)
    ,m_Inlet(nullptr)
    ,m_Outlet(nullptr)
    {

    }

    Link::Link(Inlet *inlet, Outlet *outlet, QObject *parent )
    :Item(parent)
    ,m_Inlet(inlet)
    ,m_Outlet(outlet)
    {

    }

    Link::Link(const Link &other)
    :Item(other.parent())
    ,m_Inlet(other.getInlet())
    ,m_Outlet(other.getOutlet())
    {

    }

    Inlet *Link::getInlet() const
    {
        return m_Inlet;
    }

    Outlet *Link::getOutlet() const
    {
        return m_Outlet;
    }

    void Link::link()
    {
        m_Inlet->getInletHandle().link(m_Outlet->getOutletHandle());
    }

    void Link::unlink()
    {
        m_Inlet->getInletHandle().unlinkFrom(m_Outlet->getOutletHandle());
    }
}
