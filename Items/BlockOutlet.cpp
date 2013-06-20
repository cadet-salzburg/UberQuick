#include "BlockOutlet.h"
namespace Uber {
    BlockOutlet::BlockOutlet(QObject *parent)
    :Outlet(parent)
    {

    }
    BlockOutlet::BlockOutlet(const BlockOutlet &other)
    :Outlet(other)
    ,m_OutletHandle(other.getOutletHandle())
    {

    }

    BlockOutlet::BlockOutlet(const OutletHandle &handle, QObject *parent )
    :Outlet(parent)
    ,m_OutletHandle(handle)
    {

    }

    BlockOutlet::~BlockOutlet()
    {

    }

    void BlockOutlet::setOutletHandle(const OutletHandle &handle)
    {
        m_OutletHandle = handle;
    }

    OutletHandle BlockOutlet::getOutletHandle() const
    {
        return m_OutletHandle;
    }
}
