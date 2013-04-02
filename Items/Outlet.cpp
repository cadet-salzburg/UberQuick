#include "Outlet.h"
namespace Uber {
    Outlet::Outlet(QObject *parent)
    :Item(parent)
    {

    }
    Outlet::Outlet(const Outlet &other)
    :Item(other.parent(), other.position(), other.size())
    ,m_OutletHandle(other.getOutletHandle())
    {

    }

    Outlet::Outlet(const OutletHandle &handle, QObject *parent )
    :Item(parent)
    ,m_OutletHandle(handle)
    {
    }

    Outlet::~Outlet()
    {

    }

    void Outlet::setOutletHandle(const OutletHandle &handle)
    {
        m_OutletHandle = handle;
    }

    OutletHandle Outlet::getOutletHandle() const
    {
        return m_OutletHandle;
    }
}
