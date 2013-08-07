#ifndef BLOCKOUTLET_H
#define BLOCKOUTLET_H
#include "Outlet.h"
#include "_2RealApplication.h"

using namespace _2Real::app;
namespace Uber {
    class StringModel;
    class BlockOutlet : public Outlet
    {
        Q_OBJECT
    public:
        BlockOutlet(QObject *parent = 0);
        BlockOutlet(const BlockOutlet &other);
        BlockOutlet( const  OutletHandle &handle, QObject *parent = 0 );
        virtual ~BlockOutlet();
        void                        setOutletHandle(const OutletHandle& handle );
        OutletHandle                getOutletHandle() const;

        virtual bool                isValid() const;
        StringModel*                getDataType();
        StringModel*                getDataTypeFields();
    private:
        _2Real::app::OutletHandle   m_OutletHandle;
        StringModel*                m_ConnectionOptions;
        StringModel*                m_DataType;
    public slots:
    };
}
#endif // BLOCKOUTLET_H
