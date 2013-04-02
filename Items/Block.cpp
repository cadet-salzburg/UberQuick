#include "Block.h"
#include <QDebug>
namespace Uber {

    Block::Block()
    :Item(0)
    {

    }

    Block::Block( const BlockHandle& handle )
    :Item(0)
    ,m_BlockHandle(handle)
    {
        initialize();
    }

    Block::Block(const Block &other)
    :Item(other.parent(), other.position(), other.size())
    ,m_BlockHandle(other.getBlockHandle())
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

    QList<InletRef> Block::getInlets() const
    {
        return m_Inlets;
    }

    QList<OutletRef> Block::getOutlets() const
    {
        return m_Outlets;
    }

    void Block::initialize()
    {
        if ( m_BlockHandle.isValid() )
        {
            m_Inlets.clear();
            m_Outlets.clear();

            BlockHandle::InletHandles  inlets = m_BlockHandle.getAllInletHandles();
            BlockHandle::OutletHandles outlets = m_BlockHandle.getAllOutletHandles();
            BlockHandle::InletHandleIterator iterIn = inlets.begin();
            for ( ;iterIn!=inlets.end(); ++iterIn )
            {
                InletRef currentInlet( new Inlet(*iterIn) );
                m_Inlets.push_back(currentInlet);
            }
            BlockHandle::OutletHandleIterator iterOut = outlets.begin();
            for ( ;iterOut!=outlets.end(); ++iterOut )
            {
                OutletRef currentOutlet( new Outlet(*iterOut));
                m_Outlets.push_back(currentOutlet);
            }
        }
    }

    QDebug operator<<(QDebug dbg, const Block &block )
    {
        dbg.nospace() << "Block";
        return dbg.maybeSpace();
    }
}
