#include "ConnectionManager.h"
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QDebug>
#include "../items/Item.h"
#include "../items/Link.h"
#include "../items/BlockInlet.h"
#include "../items/BlockOutlet.h"
#include "../models/ItemObjectListModel.h"

namespace Uber {
    ConnectionManager::ConnectionManager( ItemObjectListModel* itemModel )
    :QObject(nullptr)
    ,m_ItemModel(itemModel)
    {

    }

    void ConnectionManager::beginAddingLink(Item *item, const QPointF &pos )
    {
        qDebug() << "Begin adding link";
        m_Link = new Link();
        if ( item->getClassName()=="Uber::BlockInlet" )
        {
            BlockInlet *inlet = qobject_cast<BlockInlet*>(item);
            m_Link->setInlet(inlet);
            qDebug() << "---Inlet";
        } else if ( item->getClassName()== "Uber::BlockOutlet" )
        {
            BlockOutlet *outlet = qobject_cast<BlockOutlet*>(item);
            m_Link->setOutlet(outlet);
            qDebug() << "---Outlet";
        }
        updateLink(pos);
        m_ItemModel->append(m_Link);
        qDebug() << " The number of items in the model is: " << m_ItemModel->count();
    }

    void ConnectionManager::updateLink(const QPointF &pos)
    {
        if ( m_Link )
        {
            qDebug() << "Link position was updated: " << pos;
            m_Link->updatePosition(pos);
        }
    }

    void ConnectionManager::finishAddingLink(Item *item)
    {
        if ( item->getClassName()=="Uber::BlockInlet" )
        {
            m_Link->setInlet(qobject_cast<BlockInlet*>(item));
        } else if ( item->getClassName()== "Uber::BlockOutlet" )
        {
            m_Link->setOutlet(qobject_cast<BlockOutlet*>(item));
        } else
        {
            qDebug() << "Adding Link failed.!!! Need to take care of removing the item from the model";
        }
    }

    void ConnectionManager::cancelAddingLink()
    {
        if ( m_Link )
        {
            int idx = m_ItemModel->indexOf(m_Link);
            m_ItemModel->removeAt(idx);
            qDebug() << "The id is: " << idx;
        }
    }

    void ConnectionManager::startDrag(Uber::Item *item)
    {
        qDebug() << "Started drag";
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(item->getClassName());
        drag->setMimeData(mimeData);
        QPixmap pixmap(1,1);
        pixmap.fill(Qt::transparent);
        drag->setPixmap(pixmap);
        Qt::DropAction dropAction = drag->exec();
    }

    void ConnectionManager::disconnect(Link *link)
    {
    }

    bool ConnectionManager::canConnect(Item *itemA, Item *itemB)
    {
        return true;
    }
}
