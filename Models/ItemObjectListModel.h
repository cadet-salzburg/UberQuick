#ifndef ITEMOBJECTLISTMODEL_H
#define ITEMOBJECTLISTMODEL_H
#include "Models/QObjectListModelT.h"
#include "Items/Item.h"

namespace Uber {
    class ItemObjectListModel : public QObjectListModelT<Item*>
    {
    public:
        ItemObjectListModel(QObject *parent)
        :QObjectListModelT<Item*>(parent)
        {

        }
        ItemObjectListModel(const QList<Item*> &objects, QObject *parent = 0)
        :QObjectListModelT<Item*>(objects, parent)
        {
        }
        ItemObjectListModel(ItemObjectListModel*itemListModel, QObject *parent)
        :QObjectListModelT<Item*>(itemListModel, parent)
        {
        }
    };
}
#endif // ITEMOBJECTLISTMODEL_H
