#include "Block.h"
#include "BlockInlet.h"
#include "BlockOutlet.h"
#include "../Models/InletObjectListModel.h"
#include "../Models/OutletObjectListModel.h"
#include <QDebug>

namespace Uber {
    using namespace _2Real::app;
    Block::Block()
    :Item(0)
    ,m_InletModel(nullptr)
    ,m_OutletModel(nullptr)
    {
        initialize();
    }

    Block::Block( const BlockHandle& handle, QString name )
    :Item(0)
    ,m_BlockHandle(handle)
    ,m_InletModel(nullptr)
    ,m_OutletModel(nullptr)
    ,m_Name(name)
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
        delete m_InletModel;
        delete m_OutletModel;
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
    int Block::getNumberOfInlets()
    {
        return m_InletModel->count();
    }
    int Block::getNumberOfOutlets()
    {
        return m_OutletModel->count();
    }

    void Block::initialize()
    {
        if ( m_BlockHandle.isValid() )
        {
            delete m_InletModel;
            delete m_OutletModel;

            m_InletModel = new InletObjectListModel(0);
            m_OutletModel = new OutletObjectListModel(0);

            std::vector<InletHandle> inlets;
            std::vector<OutletHandle> outlets;

            m_BlockHandle.getAllInletHandles(inlets);
            m_BlockHandle.getAllOutletHandles(outlets);

            BlockHandle::InletHandleIterator iterIn = inlets.begin();
            int i =0;
            for ( ;iterIn!=inlets.end(); ++iterIn )
            {
                i++;
                BlockInlet *currentInlet( new BlockInlet(*iterIn) );
                currentInlet->setName("Inlet" + QString::number(i));
                m_InletModel->append(currentInlet);
            }
            BlockHandle::OutletHandleIterator iterOut = outlets.begin();
            for ( ;iterOut!=outlets.end(); ++iterOut )
            {
                BlockOutlet *currentOutlet( new BlockOutlet(*iterOut));
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
