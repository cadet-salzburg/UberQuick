#include "Block.h"
#include <QDebug>

namespace Uber {
    Block::Block()
    :Item(0)
    ,m_InletModel(nullptr)
    ,m_OutletModel(nullptr)
    {

    }
    Block::Block( const BlockHandle& handle )
    :Item(0)
    ,m_BlockHandle(handle)
    ,m_InletModel(nullptr)
    ,m_OutletModel(nullptr)
    {
        initialize();
    }
    Block::Block(const Block &other)
    :Item(other.parent(), other.getPosition(), other.size())
    ,m_BlockHandle(other.getBlockHandle())
    ,m_InletModel(other.getInletModel())
    ,m_OutletModel(other.getOutletModel())
    {
        initialize();
    }
    Block::~Block()
    {

    }

    void    Block::setName( QString name )
    {
        m_Name = name;
    }

    QString Block::getName()
    {
        return m_Name;
    }

    void Block::setBlockHandle( const BlockHandle& handle )
    {
        m_BlockHandle = handle;
        initialize();
    }

    BlockHandle Block::getBlockHandle() const
    {
        return m_BlockHandle;
    }

    Uber::InletObjectListModel*   Block::getInletModel() const
    {
        return m_InletModel;
    }

    Uber::OutletObjectListModel*  Block::getOutletModel() const
    {
        return m_OutletModel;
    }

    void Block::initialize()
    {
        if ( m_BlockHandle.isValid() )
        {
            delete m_InletModel;
            delete m_OutletModel;

            m_InletModel = new InletObjectListModel(0);
            m_OutletModel = new OutletObjectListModel(0);

            BlockHandle::InletHandles  inlets = m_BlockHandle.getAllInletHandles();
            BlockHandle::OutletHandles outlets = m_BlockHandle.getAllOutletHandles();
            BlockHandle::InletHandleIterator iterIn = inlets.begin();
            int i =0;
            for ( ;iterIn!=inlets.end(); ++iterIn )
            {
                i++;
                Inlet *currentInlet( new Inlet(*iterIn) );
                currentInlet->setName("Inlet" + QString::number(i));
                m_InletModel->append(currentInlet);
            }
            BlockHandle::OutletHandleIterator iterOut = outlets.begin();
            for ( ;iterOut!=outlets.end(); ++iterOut )
            {
                Outlet *currentOutlet( new Outlet(*iterOut));
                m_OutletModel->append(currentOutlet);
            }
        }
    }
    QDebug operator<<(QDebug dbg, const Block &block )
    {
        dbg.nospace() << "Block";
        return dbg.maybeSpace();
    }
}
