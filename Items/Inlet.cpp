#include "Inlet.h"
#include "Item.h"
namespace Uber {
    Inlet::Inlet(QObject *parent)
    :Item(parent)
    {

    }
    Inlet::Inlet(const Inlet &other)
    :Item(other.parent(), other.getPosition(), other.size())
    {

    }

    Inlet::~Inlet()
    {

    }
}
