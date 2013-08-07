#include "OutletObjectListModel.h"
#include "../Items/Outlet.h"

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

    OutletObjectListModel::~OutletObjectListModel()
    {
        int cnt = count();
        for ( int i =0; i< cnt; ++i )
        {
            Outlet* item = at(i);
            //emit item->killSelf();
            delete item;
        }
        removeAt(0, cnt);
    }
}
