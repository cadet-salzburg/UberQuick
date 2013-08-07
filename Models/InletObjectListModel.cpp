#include "InletObjectListModel.h"
#include "../Items/Inlet.h"
namespace Uber {
    InletObjectListModel::InletObjectListModel(QObject *parent)
    :QObjectListModelT<Inlet*>(parent)
    {

    }

    InletObjectListModel::InletObjectListModel(const QList<Inlet*> &objects, QObject *parent)
    :QObjectListModelT<Inlet*>(objects, parent)
    {

    }

    InletObjectListModel::InletObjectListModel(InletObjectListModel *inletListModel, QObject *parent)
    :QObjectListModelT<Inlet*>(inletListModel, parent)
    {

    }

    InletObjectListModel::~InletObjectListModel()
    {
        int cnt = count();
        for ( int i =0; i< cnt; ++i )
        {
            Inlet* item = at(i);
            delete item;
        }
        removeAt(0, cnt);
    }

}
