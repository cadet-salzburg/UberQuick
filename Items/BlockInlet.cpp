#include "BlockInlet.h"
#include "_2RealDatatypes.h"
namespace Uber {
    BlockInlet::BlockInlet(QObject *parent)
    :Inlet(parent)
    ,m_ConnectionOptions(nullptr)
    {

    }
    BlockInlet::BlockInlet(const BlockInlet &other)
    :Inlet(other)
    ,m_InletHandle(other.getInletHandle())
    ,m_ConnectionOptions(nullptr)
    {

    }

    BlockInlet::BlockInlet(const InletHandle &handle, QObject *parent )
    :Inlet(parent)
    ,m_InletHandle(handle)
    ,m_ConnectionOptions(nullptr)
    {

    }

    BlockInlet::~BlockInlet()
    {

    }

    void BlockInlet::setInletHandle(const InletHandle &handle)
    {
        m_InletHandle = handle;
    }

    InletHandle BlockInlet::getInletHandle() const
    {
        return m_InletHandle;
    }

    StringModel* BlockInlet::getDataTypeFields()
    {
        if ( !m_ConnectionOptions )
        {
            m_ConnectionOptions = new StringModel();
        } else
        {
            m_ConnectionOptions->clear(true);
        }
        if ( isValid() )
        {
            _2Real::app::TypeMetainfo info = m_InletHandle.getType();
            TypeMetainfo::FieldDesc d = info.getFieldInfo();
            for ( TypeMetainfo::FieldDesc::const_iterator it = d.begin(); it != d.end(); ++it )
            {
                StringObject *obj = new StringObject();
                obj->setString(QString::fromUtf8((*it).c_str()));
                m_ConnectionOptions->append(obj);
            }
        }
        return m_ConnectionOptions;
    }
}
