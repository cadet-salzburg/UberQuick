#include "ConnectionManager.h"
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QDebug>

#include "../items/Item.h"
#include "../items/Link.h"
#include "../items/FrameworkInlet.h"
#include "../items/FrameworkOutlet.h"
#include "../items/InterfaceInlet.h"
#include "../items/InterfaceOutlet.h"
#include "../models/ItemObjectListModel.h"
#include "../models/StringModel.h"

namespace Uber {
    ConnectionManager::ConnectionManager( ItemObjectListModel* itemModel )
    :QObject(nullptr)
    ,m_ItemModel(itemModel)
    {

    }


    void ConnectionManager::beginLink(Item *item, const QPointF &pos )
    {
        m_Link = new Link();
        if ( item->getClassName()=="Uber::FrameworkInlet" )
        {
            FrameworkInlet *inlet = qobject_cast<FrameworkInlet*>(item);
            m_Link->setInlet(inlet);
        } else if ( item->getClassName()== "Uber::FrameworkOutlet" )
        {
            FrameworkOutlet *outlet = qobject_cast<FrameworkOutlet*>(item);
            m_Link->setOutlet(outlet);
        } else if ( item->getClassName()== "Uber::InterfaceInlet" )
        {
            InterfaceInlet *inlet = qobject_cast<InterfaceInlet*>(item);
            m_Link->setInlet(inlet);
        }
        else if ( item->getClassName()== "Uber::InterfaceOutlet" )
        {
            InterfaceOutlet *outlet = qobject_cast<InterfaceOutlet*>(item);
            m_Link->setOutlet(outlet);
        }
        m_ItemModel->append(m_Link);
        updateLink(pos);
        startDrag(item);
    }

    void ConnectionManager::updateLink(const QPointF &pos)
    {
        if ( m_Link )
        {
            m_Link->updatePosition(pos);
        }
    }

    void ConnectionManager::finishLink(Item *item)
    {
        if ( item->getClassName()=="Uber::FrameworkInlet" )
        {
            m_Link->setInlet(qobject_cast<FrameworkInlet*>(item));
        } else if ( item->getClassName()== "Uber::FrameworkOutlet" )
        {
            m_Link->setOutlet(qobject_cast<FrameworkOutlet*>(item));
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
            qDebug() << "---BaseOutlet";
        }
        if ( !m_Link->isValid() )
        {
            removeLink();
        } else {
            m_Link->connectSignals();
        }
        if ( m_Link->isFrameworkLink() )
        {
            qDebug() << " Is a framework Link";
        } else {
            qDebug() << " Is NOT a framework Link";
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
