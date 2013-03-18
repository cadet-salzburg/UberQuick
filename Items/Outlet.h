#ifndef OUTLET_H
#define OUTLET_H

#include <QSharedPointer>
#include "Item.h"

namespace Uber {
    class Outlet : public Item
    {
        Q_OBJECT
    public:
        Outlet(QObject *parent = 0);
        Outlet(const Outlet &other);
        ~Outlet();
    signals:

    public slots:

    };
    typedef QSharedPointer<Outlet> OutletRef;
    Q_DECLARE_METATYPE(Outlet)
}
#endif // OUTLET_H
