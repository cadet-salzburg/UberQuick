#include "FrameworkOutlet.h"
#include "../models/StringModel.h"
#include "StringObject.h"
namespace Uber {
    FrameworkOutlet::FrameworkOutlet(QObject *parent)
    :BaseOutlet(parent)
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }
    FrameworkOutlet::FrameworkOutlet(const FrameworkOutlet &other)
    :BaseOutlet(other)
    ,m_OutletHandle(other.getOutletHandle())
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    FrameworkOutlet::FrameworkOutlet(const OutletHandle &handle, QObject *parent )
    :BaseOutlet(parent)
    ,m_OutletHandle(handle)
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    FrameworkOutlet::~FrameworkOutlet()
    {
        delete m_ConnectionOptions;
        delete m_DataType;
    }

    void FrameworkOutlet::setOutletHandle(const OutletHandle &handle)
    {
        m_OutletHandle = handle;
    }

    OutletHandle FrameworkOutlet::getOutletHandle() const
    {
        return m_OutletHandle;
    }

    bool FrameworkOutlet::isValid() const
    {
        return m_OutletHandle.isValid();
    }

    StringModel *FrameworkOutlet::getDataType()
    {
        if ( !m_DataType )
        {
            m_DataType = new StringModel();
        } else
        {
            m_DataType->clear(true);
        }
        if ( isValid() )
        {
            _2Real::app::TypeMetainfo info = m_OutletHandle.getType();

            std::pair< std::string, std::string > typeName = info.getTypename();
            StringObject *obj = new StringObject();
            obj->setString(QString::fromUtf8(typeName.second.c_str()));
            m_DataType->append(obj);
        }
        return m_DataType;
    }

    StringModel* FrameworkOutlet::getDataTypeFields()
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
            _2Real::DataFields fields;
            info.getDataFields( fields );

            for ( _2Real::DataFields::const_iterator it = fields.begin(); it != fields.end(); ++ it )
            {
                StringObject *obj = new StringObject();
                std::string type = (*it)->getTypename().first + "::" + (*it)->getTypename().second;
//                std::string type = (*it)->getTypename();
                obj->setString(QString::fromUtf8(type.c_str()));
                m_ConnectionOptions->append(obj);
            }
        }
        return m_ConnectionOptions;
    }
}
