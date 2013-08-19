#include "BlockInlet.h"
#include "_2RealDatatypes.h"
namespace Uber {
    BlockInlet::BlockInlet(QObject *parent)
    :Inlet(parent)
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    BlockInlet::BlockInlet(const BlockInlet &other)
    :Inlet(other)
    ,m_InletHandle(other.getInletHandle())
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    BlockInlet::BlockInlet(const InletHandle &handle, QObject *parent )
    :Inlet(parent)
    ,m_InletHandle(handle)
    ,m_ConnectionOptions(nullptr)
    ,m_DataType(nullptr)
    {

    }

    BlockInlet::~BlockInlet()
    {
        delete m_ConnectionOptions;
        delete m_DataType;
    }

    void BlockInlet::setInletHandle(const InletHandle &handle)
    {
        m_InletHandle = handle;
    }

    InletHandle BlockInlet::getInletHandle() const
    {
        return m_InletHandle;
    }

    StringModel *BlockInlet::getDataType()
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
            _2Real::DataFields fields;
            info.getDataFields( fields );

            for ( _2Real::DataFields::const_iterator it = fields.begin(); it != fields.end(); ++ it )
            {
                StringObject *obj = new StringObject();
                std::string type = (*it)->getTypename().first +"::"+(*it)->getTypename().second;
// std::string type = (*it)->getTypename();
                obj->setString(QString::fromUtf8(type.c_str()));
                m_ConnectionOptions->append(obj);
            }
        }
        return m_ConnectionOptions;
    }
}
