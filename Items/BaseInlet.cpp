#include "BaseInlet.h"
#include "Item.h"
namespace Uber {
    BaseInlet::BaseInlet(QObject *parent)
    :Item(parent)
    {
        setObjectName("Inlet");
    }
    BaseInlet::BaseInlet(const BaseInlet &other)
    :Item(other.parent(), other.getPosition(), other.size())
    {
        setObjectName("Inlet");
    }

    BaseInlet::~BaseInlet()
    {

    }
}
