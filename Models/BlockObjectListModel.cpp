#include "BlockObjectListModel.h"
namespace Uber {
    BlockObjectListModel::BlockObjectListModel(QObject *parent)
    :QObjectListModelT<Block*>(parent)
    {

    }
}
