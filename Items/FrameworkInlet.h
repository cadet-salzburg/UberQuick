#ifndef FRAMEWORKINLET_H
#define FRAMEWORKINLET_H
#include "BaseInlet.h"
#include "_2RealApplication.h"
using namespace _2Real::app;
namespace Uber {
    class StringModel;
    class FrameworkInlet : public BaseInlet
    {
       Q_OBJECT
    public:
        FrameworkInlet(QObject *parent = 0);
        FrameworkInlet( const FrameworkInlet &other );
        FrameworkInlet( const InletHandle &handle, QObject *parent = 0 );
        virtual     ~FrameworkInlet();

        InletHandle     getInletHandle() const;
        void            setInletHandle(const InletHandle& handle );

        StringModel*    getDataType();
        StringModel*    getDataTypeFields();

        bool            isValid() const;
    private:
        InletHandle     m_InletHandle;
        StringModel*    m_ConnectionOptions;
        StringModel*    m_DataType;
    };
}
#endif // FRAMEWORKINLET_H
