#include "FrameworkBlock.h"
#include "FrameworkInlet.h"
#include "FrameworkOutlet.h"
#include "InletObjectListModel.h"
#include "OutletObjectListModel.h"

namespace Uber {
    using namespace _2Real::app;
    FrameworkBlock::FrameworkBlock()
    :BaseBlock(0)
    {
        qDebug() << " constructor called";
        initialize();
    }

    FrameworkBlock::FrameworkBlock( const BlockHandle& handle, QString name )
    :BaseBlock(0)
    ,m_BlockHandle(handle)
    {
        setObjectName(name);
        initialize();
    }

    FrameworkBlock::~FrameworkBlock()
    {
        qDebug() << "Block Destructor";
        m_BlockHandle.destroy(1000);
    }

    void FrameworkBlock::setBlockHandle( const BlockHandle& handle )
    {
        m_BlockHandle = handle;
        initialize();
    }

    BlockHandle FrameworkBlock::getBlockHandle() const
    {
        return m_BlockHandle;
    }

    void FrameworkBlock::initialize()
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
                FrameworkInlet *currentInlet( new FrameworkInlet(*iterIn) );
                currentInlet->setObjectName("Inlet" + QString::number(i));
                m_InletModel->append(currentInlet);
            }
            BlockHandle::OutletHandleIterator iterOut = outlets.begin();
            for ( ;iterOut!=outlets.end(); ++iterOut )
            {
                FrameworkOutlet *currentOutlet( new FrameworkOutlet(*iterOut));
                m_OutletModel->append(currentOutlet);
            }
        }
        m_Classname = metaObject()->className();
        qDebug() << " a block was created of: " << m_Classname;
    }
}
