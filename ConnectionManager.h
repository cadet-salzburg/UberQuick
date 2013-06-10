#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <QObject>
#include <QPoint>
namespace Uber {

    class Item;
    class Link;
    class ItemObjectListModel;
    class ConnectionManager : public QObject
    {
        Q_OBJECT
    public:
        ConnectionManager( ItemObjectListModel* itemModel );
        Q_INVOKABLE void        beginAddingLink( Uber::Item* item, const QPointF &pos );
        Q_INVOKABLE void        updateLink( const QPointF& pos );
        Q_INVOKABLE void        finishAddingLink( Item* item );
        Q_INVOKABLE void        startDrag( Uber::Item* item );
        void                    disconnect(Link* link);
    private:
        Link                    *m_Link;
        ItemObjectListModel     *m_ItemModel;
        bool    canConnect( Item* itemA, Item* itemB );
    };
}
#endif // CONNECTIONMANAGER_H
