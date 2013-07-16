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
            _2Real::Fields fields;
            info.getFieldInfo( fields );

            for ( _2Real::Fields::const_iterator it = fields.begin(); it != fields.end(); ++ it )
            {
                StringObject *obj = new StringObject();
                obj->setString(QString::fromUtf8((*it)->getTypename().c_str()));
                m_ConnectionOptions->append(obj);
            }
        }
        return m_ConnectionOptions;
    }
}
