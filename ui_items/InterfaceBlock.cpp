#include "InterfaceBlock.h"
#include "BaseInlet.h"
#include "BaseOutlet.h"
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

    void InterfaceBlock::appendInlet(BaseInlet *inlet)
    {
        m_InletModel->append(inlet);
    }

    void InterfaceBlock::appendOutlet(BaseOutlet *outlet)
    {
        m_OutletModel->append(outlet);
    }
}
