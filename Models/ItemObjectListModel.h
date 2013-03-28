#ifndef ITEMOBJECTLISTMODEL_H
#define ITEMOBJECTLISTMODEL_H
#include "QObjectListModelT.h"
#include "BlockObjectListModel.h"
#include "../Items/Item.h"

namespace Uber {
    class ItemObjectListModel : public QObjectListModelT<Item*>
    {
    public:
        ItemObjectListModel( QObject *parent );
        ItemObjectListModel( const QList<Item*> &objects, QObject *parent = 0 );
        ItemObjectListModel( ItemObjectListModel*itemListModel, QObject *parent );
        void append(Item *item);
        QVariant data( const QModelIndex &index, int role ) const;
        BlockObjectListModel*   m_BlockModel;
    };
}
#endif // ITEMOBJECTLISTMODEL_H
