#include "BlockObjectListModel.h"

namespace Uber {
    BlockObjectListModel::BlockObjectListModel(QObject *parent)
    :QObjectListModelT<Block*>(parent)
    {

    }
    BlockObjectListModel::BlockObjectListModel(const QList<Block*> &objects, QObject *parent = 0)
    :QObjectListModelT<Block*>(objects, parent)
    {

    }
    BlockObjectListModel::BlockObjectListModel(BlockObjectListModel*blockListModel, QObject *parent)
    :QObjectListModelT<Block*>(blockListModel, parent)
    {

    }
}
