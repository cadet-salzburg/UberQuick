#include "InterfaceElement.h"
#include "Inlet.h"
#include "Outlet.h"
#include "../Models/InletObjectListModel.h"
#include "../Models/OutletObjectListModel.h"

namespace Uber {
    InterfaceElement::InterfaceElement()
    :Item(0)
    ,m_InletModel(new InletObjectListModel(0))
    ,m_OutletModel(new OutletObjectListModel(0))
    {

    }
    InterfaceElement::~InterfaceElement()
    {
        delete m_InletModel;
        delete m_OutletModel;
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

    int InterfaceElement::getNumberOfInlets()
    {
        return m_InletModel->count();
    }

    int InterfaceElement::getNumberOfOutlets()
    {
        return m_OutletModel->count();
    }

    void InterfaceElement::appendInlet(Inlet *inlet)
    {
        m_InletModel->append(inlet);
    }

    void InterfaceElement::appendOutlet(Outlet *outlet)
    {
        m_OutletModel->append(outlet);
    }
}
