#include "ItemObjectListModel.h"
#include "../items/Item.h"
#include "../Items/FrameworkBlock.h"
#include "../Items/Link.h"
#include "../ui_items//SliderBlock.h"
#include "../ui_items/TextIO.h"
#include "../ui_items/Image.h"

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

    ItemObjectListModel::~ItemObjectListModel()
    {
        int cnt = count();
        for ( int i =0; i< cnt; ++i )
        {
            Item* item = at(i);
            delete item;
        }
        removeAt(0, cnt);
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
                return QVariant::fromValue(dynamic_cast<FrameworkBlock*>(obj));
            } else if ( obj->getClassName()== QString("Uber::Link") )
            {
                return QVariant::fromValue(dynamic_cast<Link*>(obj));
            } else if ( obj->getClassName()== QString("Uber::SliderBlock") )
            {
                return QVariant::fromValue(dynamic_cast<SliderBlock*>(obj));
            }  else if ( obj->getClassName()== QString("Uber::TextIO") )
            {
                return QVariant::fromValue(dynamic_cast<TextIO*>(obj));
            } else if ( obj->getClassName()== QString("Uber::Image") )
            {
                return QVariant::fromValue(dynamic_cast<Image*>(obj));
            }
        }
        case Qt::DisplayRole:
            return QVariant::fromValue(m_objects.at(index.row())->objectName());
        }
        return QVariant();
    }
}
