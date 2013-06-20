#include "BlockInlet.h"
namespace Uber {
BlockInlet::BlockInlet(QObject *parent)
:Inlet(parent)
{

}
BlockInlet::BlockInlet(const BlockInlet &other)
:Inlet(other)
,m_InletHandle(other.getInletHandle())
{

}

BlockInlet::BlockInlet(const InletHandle &handle, QObject *parent )
:Inlet(parent)
,m_InletHandle(handle)
{

}

BlockInlet::~BlockInlet()
{

}

void BlockInlet::setInletHandle(const InletHandle &handle)
{
    m_InletHandle = handle;
}

InletHandle BlockInlet::getInletHandle() const
{
    return m_InletHandle;
}
}
