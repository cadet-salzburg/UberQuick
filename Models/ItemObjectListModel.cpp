#include "ItemObjectListModel.h"
namespace Uber {
    ItemObjectListModel::ItemObjectListModel(QObject *parent)
    :QObjectListModelT<Item*>(parent)
    ,m_BlockModel(nullptr)
    {
        m_BlockModel = new BlockObjectListModel(nullptr);
    }

    ItemObjectListModel::ItemObjectListModel(const QList<Item*> &objects, QObject *parent )
    :QObjectListModelT<Item*>(objects, parent)
    ,m_BlockModel(nullptr)
    {
        m_BlockModel = new BlockObjectListModel(nullptr);
    }

    ItemObjectListModel::ItemObjectListModel(ItemObjectListModel*itemListModel, QObject *parent )
    :QObjectListModelT<Item*>(itemListModel, parent)
    ,m_BlockModel(nullptr)
    {
        m_BlockModel = new BlockObjectListModel(nullptr);
    }

    void ItemObjectListModel::append(Item *item)
    {
        if ( item && item->getClassName()== QString("Uber::Block"))
        {
            beginInsertRows(QModelIndex(), count(), count());//nAmount );
            QObjectListModelT<Item*>::append(item);
            m_BlockModel->append(item);
            endInsertRows();
        }
    }

    QVariant ItemObjectListModel::data(const QModelIndex &index, int role ) const
    {
       // Q_UNUSED(role)
        QVariant res = QObjectListModelT<Item*>::data(index, role );
        if ( res.typeName()== QString("Uber::Block") )
        {
            return m_BlockModel->data(index,role);
        } else
        {
            return QVariant();
        }
    }
}
