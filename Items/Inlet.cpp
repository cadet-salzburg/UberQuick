#include "Inlet.h"

namespace Uber {
    Inlet::Inlet(QObject *parent)
    :Item(parent)
    {

    }
    Inlet::Inlet(const Inlet &other)
    :Item(other.parent(), other.position(), other.size())
    {

    }
    Inlet::~Inlet()
    {

    }
}
