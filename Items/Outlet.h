#ifndef OUTLET_H
#define OUTLET_H

#include <QSharedPointer>
#include "Item.h"
#include "_2RealApplication.h"

using namespace _2Real::app;
namespace Uber {
    class Outlet : public Item
    {
        Q_OBJECT
    public:
        Outlet(QObject *parent = 0);
        Outlet(const Outlet &other);
        Outlet( const   OutletHandle &handle, QObject *parent = 0 );
        ~Outlet();
        void            setOutletHandle(const OutletHandle& handle );
        OutletHandle    getOutletHandle() const;
    private:
        OutletHandle    m_OutletHandle;
    signals:
    public slots:
    };
    typedef QSharedPointer<Outlet> OutletRef;
    Q_DECLARE_METATYPE(Outlet)
}
#endif // OUTLET_H
