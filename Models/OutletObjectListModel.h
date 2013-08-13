#ifndef OUTLETOBJECTLISTMODEL_H
#define OUTLETOBJECTLISTMODEL_H
#include "QObjectListModelT.h"


namespace Uber {
    class BaseOutlet;
    class OutletObjectListModel : public QObjectListModelT<BaseOutlet*>
    {
        Q_OBJECT
    public:
        OutletObjectListModel(QObject *parent = nullptr);
        OutletObjectListModel(const QList<BaseOutlet*> &objects, QObject *parent = 0);
        OutletObjectListModel(OutletObjectListModel *outletListModel, QObject *parent);
        virtual ~OutletObjectListModel();
    };
}
#endif // OUTLETOBJECTLISTMODEL_H
