#ifndef FRAMEWORKOUTLET_H
#define FRAMEWORKOUTLET_H
#include "BaseOutlet.h"
#include "_2RealApplication.h"

using namespace _2Real::app;
namespace Uber {
    class StringModel;
    class FrameworkOutlet : public BaseOutlet
    {
        Q_OBJECT
    public:
        FrameworkOutlet(QObject *parent = 0);
        FrameworkOutlet(const FrameworkOutlet &other);
        FrameworkOutlet( const  OutletHandle &handle, QObject *parent = 0 );
        virtual ~FrameworkOutlet();

        OutletHandle                getOutletHandle() const;
        void                        setOutletHandle(const OutletHandle& handle );

        StringModel*                getDataType();
        StringModel*                getDataTypeFields();

        bool                        isValid() const;
    private:
        _2Real::app::OutletHandle   m_OutletHandle;
        StringModel*                m_ConnectionOptions;
        StringModel*                m_DataType;
    public slots:
    };
}
#endif // FRAMEWORKOUTLET_H
