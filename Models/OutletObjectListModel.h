#ifndef OUTLETOBJECTLISTMODEL_H
#define OUTLETOBJECTLISTMODEL_H
#include "QObjectListModelT.h"


namespace Uber {
    class Outlet;
    class OutletObjectListModel : public QObjectListModelT<Outlet*>
    {
        Q_OBJECT
    public:
        OutletObjectListModel(QObject *parent = nullptr);
        OutletObjectListModel(const QList<Outlet*> &objects, QObject *parent = 0);
        OutletObjectListModel(OutletObjectListModel *outletListModel, QObject *parent);
        virtual ~OutletObjectListModel();
    };
}
#endif // OUTLETOBJECTLISTMODEL_H
