#include "SystemModel.h"

namespace Uber {
    SystemModel::SystemModel(QObject *parent)
    :QAbstractItemModel(parent)
    {

    }
    int SystemModel::rowCount( const QModelIndex& parent ) const
    {
        Q_UNUSED(parent);
        return 0;
    }
    QVariant    SystemModel::data(const QModelIndex &index, int role) const
    {
        return QVariant();
    }
    bool    SystemModel::setData(const QModelIndex & index, const QVariant & value, int role)
    {
        return false;
    }
    Qt::ItemFlags SystemModel::flags(const QModelIndex & index) const
    {
        return Qt::ItemIsEditable;
    }
    bool    SystemModel::insertRows(int row, int count, const QModelIndex & parent )
    {
        return false;
    }
    bool    SystemModel::removeRows(int row, int count, const QModelIndex & parent )
    {
        return false;
    }
    void SystemModel::setModel( ModelType m,  QAbstractItemModel * model )
    {

    }
    QModelIndex SystemModel::mapFromSource ( const QModelIndex & sourceIndex ) const
    {
        return QModelIndex();
    }
    QModelIndex SystemModel::mapToSource ( const QModelIndex & proxyIndex ) const
    {
        return QModelIndex();
    }
}
