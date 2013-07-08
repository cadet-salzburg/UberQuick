#include "BlockOutlet.h"
namespace Uber {
    BlockOutlet::BlockOutlet(QObject *parent)
    :Outlet(parent)
    ,m_ConnectionOptions(nullptr)
    {

    }
    BlockOutlet::BlockOutlet(const BlockOutlet &other)
    :Outlet(other)
    ,m_OutletHandle(other.getOutletHandle())
    ,m_ConnectionOptions(nullptr)
    {

    }

    BlockOutlet::BlockOutlet(const OutletHandle &handle, QObject *parent )
    :Outlet(parent)
    ,m_OutletHandle(handle)
    ,m_ConnectionOptions(nullptr)
    {

    }

    BlockOutlet::~BlockOutlet()
    {

    }

    void BlockOutlet::setOutletHandle(const OutletHandle &handle)
    {
        m_OutletHandle = handle;
    }

    OutletHandle BlockOutlet::getOutletHandle() const
    {
        return m_OutletHandle;
    }

    StringModel* BlockOutlet::getDataTypeFields()
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
            _2Real::app::TypeMetainfo info = m_OutletHandle.getType();
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
