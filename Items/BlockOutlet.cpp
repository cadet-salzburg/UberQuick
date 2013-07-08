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
