#ifndef LINKOBJECTLISTMODEL_H
#define LINKOBJECTLISTMODEL_H
#include "QObjectListModelT.h"
#include "Items/Item.h"

namespace Uber {

    class Link : public Item {
        //
    };

    class LinkObjectListModel :public QObjectlistModelT<Link*>
    {
    public:
        LinkObjectListModel();
        LinkObjectListModel(const QList<Link*> &objects, QObject *parent = 0);
        LinkObjectListModel(LinkObjectListModel*linkListModel, QObject *parent);
    };
}
#endif // LINKOBJECTLISTMODEL_H
