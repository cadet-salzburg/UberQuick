#include "BaseBlock.h"
#include "InletObjectListModel.h"
#include "OutletObjectListModel.h"
namespace Uber {
BaseBlock::BaseBlock(QObject *parent)
:Item(parent)
,m_InletModel(nullptr)
,m_OutletModel(nullptr)
{

}

BaseBlock::~BaseBlock()
{
    qDebug() << "BaseBlock Destructor";
    delete m_InletModel;
    delete m_OutletModel;
}

InletObjectListModel *BaseBlock::getInletModel() const
{
    return m_InletModel;
}

OutletObjectListModel *BaseBlock::getOutletModel() const
{
    return m_OutletModel;
}

int BaseBlock::getNumberOfInlets()
{
    if( !m_InletModel )
        return 0;
    return m_InletModel->count();
}

int BaseBlock::getNumberOfOutlets()
{
    if ( !m_OutletModel )
        return 0;
    return m_OutletModel->count();
}
}
