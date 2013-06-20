#include "InterfaceElement.h"
namespace Uber {
InterfaceElement::InterfaceElement()
:Item(0)
,m_InletModel(new InletObjectListModel(0))
,m_OutletModel(new OutletObjectListModel(0))
{

}

InterfaceElement::InterfaceElement(const InterfaceElement &other)
:Item(other.parent(), other.getPosition(), other.size())
,m_InletModel(other.getInletModel())
,m_OutletModel(other.getOutletModel())
{
    initialize();
}

InterfaceElement::~InterfaceElement()
{

}

void    InterfaceElement::setName( QString name )
{
    m_Name = name;
}

QString InterfaceElement::getName()
{
    return m_Name;
}

Uber::InletObjectListModel*   InterfaceElement::getInletModel() const
{
    return m_InletModel;
}

Uber::OutletObjectListModel*  InterfaceElement::getOutletModel() const
{
    return m_OutletModel;
}
