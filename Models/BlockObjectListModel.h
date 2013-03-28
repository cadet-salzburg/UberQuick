#ifndef BLOCKOBJECTLISTMODEL_H
#define BLOCKOBJECTLISTMODEL_H
#include "QObjectListModelT.h"
#include "../Items/Block.h"

namespace Uber {
    class BlockObjectListModel :public QObjectListModelT<Block*>
    {
    public:
        BlockObjectListModel(QObject *parent);
        BlockObjectListModel(const QList<Block*> &objects, QObject *parent = 0);
        BlockObjectListModel(BlockObjectListModel*blockListModel, QObject *parent);
    };
}
#endif // BLOCKOBJECTLISTMODEL_H
