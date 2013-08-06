#include "ConnectionManager.h"
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QDebug>
#include "../items/Item.h"
#include "../items/Link.h"
#include "../items/BlockInlet.h"
#include "../items/BlockOutlet.h"
#include "../items/InterfaceInlet.h"
#include "../items/InterfaceOutlet.h"
#include "../models/ItemObjectListModel.h"

namespace Uber {
    ConnectionManager::ConnectionManager( ItemObjectListModel* itemModel )
    :QObject(nullptr)
    ,m_ItemModel(itemModel)
    {

    }


    void ConnectionManager::beginLink(Item *item, const QPointF &pos )
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
        } else if ( item->getClassName()== "Uber::InterfaceInlet" )
        {
            InterfaceInlet *inlet = qobject_cast<InterfaceInlet*>(item);
            m_Link->setInlet(inlet);
            qDebug() << "---Inlet";
        }
        else if ( item->getClassName()== "Uber::InterfaceOutlet" )
        {
            InterfaceOutlet *outlet = qobject_cast<InterfaceOutlet*>(item);
            m_Link->setOutlet(outlet);
            qDebug() << "---Outlet";
        }
        m_ItemModel->append(m_Link);
        updateLink(pos);
        startDrag(item);
    }

    void ConnectionManager::updateLink(const QPointF &pos)
    {
        if ( m_Link )
        {
            qDebug() << "Link position was updated: " << pos;
            m_Link->updatePosition(pos);
        }
    }

    void ConnectionManager::finishLink(Item *item)
    {
        if ( item->getClassName()=="Uber::BlockInlet" )
        {
            m_Link->setInlet(qobject_cast<BlockInlet*>(item));
        } else if ( item->getClassName()== "Uber::BlockOutlet" )
        {
            m_Link->setOutlet(qobject_cast<BlockOutlet*>(item));
        } else if ( item->getClassName()== "Uber::InterfaceInlet" )
        {
            InterfaceInlet *inlet = qobject_cast<InterfaceInlet*>(item);
            m_Link->setInlet(inlet);
            qDebug() << "---Inlet";
        }

        else if ( item->getClassName()== "Uber::InterfaceOutlet" )
        {
            InterfaceOutlet *outlet = qobject_cast<InterfaceOutlet*>(item);
            m_Link->setOutlet(outlet);
            qDebug() << "---Outlet";
        }
        if ( !m_Link->isValid() )
        {
            removeLink();
        } else {
            m_Link->connectSignals();
        }
    }

    void ConnectionManager::removeLink( Link* link )
    {
        if ( !link )
        {
            if ( m_Link )
            {
                link = m_Link;

            } else {
                return;
            }
        }
        int idx = m_ItemModel->indexOf(link);
        delete link;
        m_ItemModel->removeAt(idx);
    }

    void ConnectionManager::startDrag(Uber::Item *item)
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(item->getClassName());
        drag->setMimeData(mimeData);
        QPixmap pixmap(1,1);
        pixmap.fill(Qt::transparent);
        drag->setPixmap(pixmap);
        Qt::DropAction dropAction = drag->exec();
    }

    StringModel* ConnectionManager::getConnectionOptions()
    {
        //StringModelRef options;
        if ( m_Link )
        {
            return m_Link->getConnectionOptions();
        } else {
            return nullptr;
        }
    }

    StringModel *ConnectionManager::getConnectionTypename()
    {
        if ( m_Link )
        {
            return m_Link->getConnectionTypename();
        } else {
            return nullptr;
        }
    }

    bool ConnectionManager::canConnect(Item *itemA, Item *itemB)
    {
        return true;
    }
}
