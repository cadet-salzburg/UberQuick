#include "OutletObjectListModel.h"
#include "../Items/BaseOutlet.h"

namespace Uber {
    OutletObjectListModel::OutletObjectListModel(QObject *parent)
    :QObjectListModelT<BaseOutlet*>(parent)
    {

    }

    OutletObjectListModel::OutletObjectListModel(const QList<BaseOutlet*> &objects, QObject *parent)
    :QObjectListModelT<BaseOutlet*>(objects, parent)
    {

    }

    OutletObjectListModel::OutletObjectListModel(OutletObjectListModel *outletListModel, QObject *parent)
    :QObjectListModelT<BaseOutlet*>(outletListModel, parent)
    {

    }

    OutletObjectListModel::~OutletObjectListModel()
    {
        int cnt = count();
        for ( int i =0; i< cnt; ++i )
        {
            BaseOutlet* item = at(i);
            //emit item->killSelf();
            delete item;
        }
        removeAt(0, cnt);
    }
}
