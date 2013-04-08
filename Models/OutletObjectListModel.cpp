#include "OutletObjectListModel.h"
namespace Uber {
    OutletObjectListModel::OutletObjectListModel(QObject *parent)
    :QObjectListModelT<Outlet*>(parent)
    {

    }

    OutletObjectListModel::OutletObjectListModel(const QList<Outlet*> &objects, QObject *parent)
    :QObjectListModelT<Outlet*>(objects, parent)
    {

    }

    OutletObjectListModel::OutletObjectListModel(OutletObjectListModel *outletListModel, QObject *parent)
    :QObjectListModelT<Outlet*>(outletListModel, parent)
    {

    }
}
