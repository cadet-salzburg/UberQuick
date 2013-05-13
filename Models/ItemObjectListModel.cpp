#include "ItemObjectListModel.h"
#include "../Items/Block.h"
#include "../Items/Link.h"

namespace Uber {
    ItemObjectListModel::ItemObjectListModel(QObject *parent)
    :QObjectListModelT<Item*>(parent)
    {

    }

    ItemObjectListModel::ItemObjectListModel(const QList<Item*> &objects, QObject *parent )
    :QObjectListModelT<Item*>(objects, parent)
    {

    }

    ItemObjectListModel::ItemObjectListModel(ItemObjectListModel*itemListModel, QObject *parent )
    :QObjectListModelT<Item*>(itemListModel, parent)
    {

    }

    QVariant ItemObjectListModel::data(const QModelIndex &index, int role ) const
    {
        if (index.row() < 0 || index.row() >= m_objects.size())
            return QVariant();

        switch (role)
        {
        case QObjectListModel::ObjectRole:
        {
            Item *obj = this->at(index.row());
            if ( obj->getClassName()== QString("Uber::Block") )
            {
                return QVariant::fromValue(dynamic_cast<Block*>(obj));
            } else if ( obj->getClassName()== QString("Uber::Link") )
            {
                return QVariant::fromValue(dynamic_cast<Link*>(obj));
            }
        }
        case Qt::DisplayRole:
            return QVariant::fromValue(m_objects.at(index.row())->objectName());
        }
        return QVariant();
    }
}
