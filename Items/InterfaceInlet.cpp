#include "InterfaceInlet.h"
namespace Uber {
InterfaceInlet::InterfaceInlet(QObject *parent)
:Inlet(parent)
{

}
InterfaceInlet::InterfaceInlet(const InterfaceInlet &other)
:Inlet(other)
,m_InletHandle(other.getInletHandle())
{

}

InterfaceInlet::InterfaceInlet(const InletHandle &handle, QObject *parent )
:Inlet(parent)
,m_InletHandle(handle)
{

}

InterfaceInlet::~InterfaceInlet()
{

}

void InterfaceInlet::setInletHandle(const InletHandle &handle)
{
    m_InletHandle = handle;
}

InletHandle InterfaceInlet::getInletHandle() const
{
    return m_InletHandle;
}
}
