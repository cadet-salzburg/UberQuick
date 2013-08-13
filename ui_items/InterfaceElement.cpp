#include "InterfaceBlock.h"
#include "Inlet.h"
#include "Outlet.h"
#include "InletObjectListModel.h"
#include "OutletObjectListModel.h"
namespace Uber {
    InterfaceBlock::InterfaceBlock()
    :BaseBlock(0)
    {
        m_InletModel = new InletObjectListModel(0);
        m_OutletModel = new OutletObjectListModel(0);
    }
    InterfaceBlock::~InterfaceBlock()
    {
        qDebug() << "InterfaceBlock Destructor";
    }

    void InterfaceBlock::appendInlet(Inlet *inlet)
    {
        m_InletModel->append(inlet);
    }

    void InterfaceBlock::appendOutlet(Outlet *outlet)
    {
        m_OutletModel->append(outlet);
    }
}
