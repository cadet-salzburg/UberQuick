#include "BlockObjectListModel.h"

namespace Uber {
    BlockObjectListModel::BlockObjectListModel(QObject *parent)
    :QObjectListModelT<Block*>(parent)
    {

    }
    BlockObjectListModel::BlockObjectListModel(const QList<Block*> &objects, QObject *parent)
    :QObjectListModelT<Block*>(objects, parent)
    {

    }
    BlockObjectListModel::BlockObjectListModel(BlockObjectListModel*blockListModel, QObject *parent)
    :QObjectListModelT<Block*>(blockListModel, parent)
    {

    }
}
