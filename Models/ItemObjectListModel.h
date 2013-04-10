#ifndef ITEMOBJECTLISTMODEL_H
#define ITEMOBJECTLISTMODEL_H
#include "QObjectListModelT.h"
#include "../Items/Item.h"

namespace Uber {
    class ItemObjectListModel : public QObjectListModelT<Item*>
    {
    public:
        ItemObjectListModel( QObject *parent = nullptr );
        ItemObjectListModel( const QList<Item*> &objects, QObject *parent = 0 );
        ItemObjectListModel( ItemObjectListModel*itemListModel, QObject *parent );
        QVariant data( const QModelIndex &index, int role ) const;
    };
}
#endif // ITEMOBJECTLISTMODEL_H
