#ifndef OUTLETOBJECTLISTMODEL_H
#define OUTLETOBJECTLISTMODEL_H
#include "QObjectListModelT.h"
#include "../Items/Outlet.h"

namespace Uber {
    class OutletObjectListModel : public QObjectListModelT<Outlet*>
    {
        Q_OBJECT
    public:
        OutletObjectListModel(QObject *parent = nullptr);
        OutletObjectListModel(const QList<Outlet*> &objects, QObject *parent = 0);
        OutletObjectListModel(OutletObjectListModel *outletListModel, QObject *parent);
    };
}
#endif // OUTLETOBJECTLISTMODEL_H
