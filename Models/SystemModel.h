#ifndef SYSTEMMODEL_H
#define SYSTEMMODEL_H

#include <QAbstractItemModel>
//#include <QObjectListModel>
#include "BlockModel.h"
#include "../Items/Connection.h"

namespace Uber {
    typedef enum {
        BlockType       = 1,
        UiType          = 2,
        ConnectionType  = 3
    } ModelType;

    class SystemModel : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        explicit        SystemModel(QObject *parent = 0);
        //Needed methods
        int             rowCount( const QModelIndex& parent = QModelIndex() ) const;
        QVariant        data(const QModelIndex &index, int role = Qt::DisplayRole ) const;

        bool            setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
        Qt::ItemFlags   flags(const QModelIndex & index) const;

        bool            insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
        bool            removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
        //Our methods
        void            setModel( ModelType m,  QAbstractItemModel * model );
        QModelIndex     mapFromSource ( const QModelIndex & sourceIndex ) const;
        QModelIndex     mapToSource ( const QModelIndex & proxyIndex ) const;
    signals:
    public slots:
    private:
        QMap< ModelType, QAbstractItemModel* > m_Models;
    };
}
#endif // SYSTEMMODEL_H
