#include "BaseOutlet.h"
namespace Uber {
    BaseOutlet::BaseOutlet(QObject *parent)
    :Item(parent)
    {
        setObjectName("BaseOutlet");
    }
    BaseOutlet::BaseOutlet(const BaseOutlet &other)
    :Item(other.parent(), other.getPosition(), other.size())
    {
        setObjectName("BaseOutlet");
    }
    BaseOutlet::~BaseOutlet()
    {

    }
}
