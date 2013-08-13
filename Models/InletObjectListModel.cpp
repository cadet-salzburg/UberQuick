#include "InletObjectListModel.h"
#include "../Items/BaseInlet.h"
namespace Uber {
    InletObjectListModel::InletObjectListModel(QObject *parent)
    :QObjectListModelT<BaseInlet*>(parent)
    {

    }

    InletObjectListModel::InletObjectListModel(const QList<BaseInlet*> &objects, QObject *parent)
    :QObjectListModelT<BaseInlet*>(objects, parent)
    {

    }

    InletObjectListModel::InletObjectListModel(InletObjectListModel *inletListModel, QObject *parent)
    :QObjectListModelT<BaseInlet*>(inletListModel, parent)
    {

    }

    InletObjectListModel::~InletObjectListModel()
    {
        int cnt = count();
        for ( int i =0; i< cnt; ++i )
        {
            BaseInlet* item = at(i);
            delete item;
        }
        removeAt(0, cnt);
    }

}
