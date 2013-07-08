#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <QObject>
#include <QPoint>
#include "StringModel.h"
namespace Uber {

    class Item;
    class Link;
    class ItemObjectListModel;
    class ConnectionManager : public QObject
    {
        Q_OBJECT
    public:
        ConnectionManager( ItemObjectListModel* itemModel );

        Q_INVOKABLE void                beginLink( Uber::Item* item, const QPointF &pos );
        Q_INVOKABLE void                updateLink( const QPointF& pos );
        Q_INVOKABLE void                finishLink( Uber::Item* item );
        Q_INVOKABLE void                removeLink( Link* link = nullptr );

        Q_INVOKABLE Uber::StringModel*  getConnectionOptions();

    private:
        Link*                           m_Link;
        ItemObjectListModel*            m_ItemModel;
        bool                            canConnect( Item* itemA, Item* itemB );
        void                            startDrag( Uber::Item* item );
    };
}
#endif // CONNECTIONMANAGER_H
