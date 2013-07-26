#ifndef BLOCKOUTLET_H
#define BLOCKOUTLET_H

#include <QSharedPointer>
#include "Outlet.h"
#include "StringModel.h"
#include "_2RealApplication.h"

using namespace _2Real::app;
namespace Uber {
    class BlockOutlet : public Outlet
    {
        Q_OBJECT
    public:
        BlockOutlet(QObject *parent = 0);
        BlockOutlet(const BlockOutlet &other);
        BlockOutlet( const   OutletHandle &handle, QObject *parent = 0 );
        virtual ~BlockOutlet();
        void            setOutletHandle(const OutletHandle& handle );
        OutletHandle    getOutletHandle() const;

        virtual inline bool     isValid() const
        {
            return m_OutletHandle.isValid();
        }
        StringModel*                  getDataType();
        StringModel*     getDataTypeFields();
    private:
        OutletHandle    m_OutletHandle;
        StringModel*                    m_ConnectionOptions;
        StringModel*                    m_DataType;
    public slots:
    };
    typedef QSharedPointer<BlockOutlet> BlockOutletRef;
    Q_DECLARE_METATYPE(BlockOutlet)
}
#endif // BLOCKOUTLET_H
