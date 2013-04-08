#include "InletObjectListModel.h"
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
}
