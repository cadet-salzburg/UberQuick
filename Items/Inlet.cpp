#include "Inlet.h"

namespace Uber {
    Inlet::Inlet(QObject *parent)
    :Item(parent)
    {

    }
    Inlet::Inlet(const Inlet &other)
    :Item(other.parent(), other.getPosition(), other.size())
    ,m_InletHandle(other.getInletHandle())
    {

    }

    Inlet::Inlet(const InletHandle &handle, QObject *parent )
    :Item(parent)
    ,m_InletHandle(handle)
    {
    }

    Inlet::~Inlet()
    {

    }

    void Inlet::setInletHandle(const InletHandle &handle)
    {
        m_InletHandle = handle;
    }

    InletHandle Inlet::getInletHandle() const
    {
        return m_InletHandle;
    }
}
