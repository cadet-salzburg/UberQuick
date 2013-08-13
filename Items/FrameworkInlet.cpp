#include "FrameworkInlet.h"
#include "_2RealDatatypes.h"
#include "StringModel.h"
#include "StringObject.h"
namespace Uber {
    FrameworkInlet::FrameworkInlet(QObject *parent)
    :BaseInlet(parent)
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    FrameworkInlet::FrameworkInlet(const FrameworkInlet &other)
    :BaseInlet(other)
    ,m_InletHandle(other.getInletHandle())
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    FrameworkInlet::FrameworkInlet(const InletHandle &handle, QObject *parent )
    :BaseInlet(parent)
    ,m_InletHandle(handle)
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    FrameworkInlet::~FrameworkInlet()
    {
        delete m_ConnectionOptions;
        delete m_DataType;
    }

    void FrameworkInlet::setInletHandle(const InletHandle &handle)
    {
        m_InletHandle = handle;
    }

    InletHandle FrameworkInlet::getInletHandle() const
    {
        return m_InletHandle;
    }

    bool FrameworkInlet::isValid() const
    {
        return m_InletHandle.isValid();
    }

    StringModel *FrameworkInlet::getDataType()
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
            _2Real::app::TypeMetainfo info = m_InletHandle.getType();

            std::pair< std::string, std::string > typeName = info.getTypename();
            StringObject *obj = new StringObject();
            obj->setString(QString::fromUtf8(typeName.second.c_str()));
            m_DataType->append(obj);
        }
        return m_DataType;
    }

    StringModel* FrameworkInlet::getDataTypeFields()
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
            _2Real::DataFields fields;
            info.getDataFields( fields );

            for ( _2Real::DataFields::const_iterator it = fields.begin(); it != fields.end(); ++ it )
            {
                StringObject *obj = new StringObject();
                std::string type = (*it)->getTypename().first +"::"+(*it)->getTypename().second;
//                std::string type = (*it)->getTypename();
                obj->setString(QString::fromUtf8(type.c_str()));
                m_ConnectionOptions->append(obj);
            }
        }
        return m_ConnectionOptions;
    }
}
