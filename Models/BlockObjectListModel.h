#ifndef BLOCKOBJECTLISTMODEL_H
#define BLOCKOBJECTLISTMODEL_H

#include "Models/QObjectListModelT.h"

namespace Uber {
    class BlockObjectListModel : public QObjectListModelT<Block*>
    {
    public:
    explicit BlockObjectListModel(QObject *parent = 0);
    signals:
    public slots:
    };
}
#endif // BLOCKOBJECTLISTMODEL_H
