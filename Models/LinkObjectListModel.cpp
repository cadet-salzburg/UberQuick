#include "LinkObjectListModel.h"

namespace Uber {
    LinkObjectListModel::LinkObjectListModel(QObject *parent)
    :QObjectListModelT<Link*>(parent)
    {

    }
    LinkObjectListModel::LinkObjectListModel(const QList<Block*> &objects, QObject *parent = 0)
    :QObjectListModelT<Link*>(objects, parent)
    {

    }
    LinkObjectListModel::LinkObjectListModel(BlockObjectListModel*blockListModel, QObject *parent)
    :QObjectListModelT<Link*>(blockListModel, parent)
    {

    }
}
