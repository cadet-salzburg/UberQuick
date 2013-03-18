#include "DataflowModel.h"

namespace Uber {

DataflowModel::DataflowModel(QObject *parent)
:QAbstractListModel(parent)
{

}

int DataflowModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return count();
}

QVariant DataflowModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    if (index.row() < 0 || index.row() >= count())
        return QVariant();
    return QVariant::fromValue( QString( m_Entries.at(index.row())->getClassName()));
}

void DataflowModel::addEntry(Item* entry)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Entries << entry;
    endInsertRows();
    emit countChanged();
}


inline int DataflowModel::count() const
{
    return m_Entries.count();
}

QHash<int,QByteArray> DataflowModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ModelTypeRole] = "modeltype";
    roles[DimRole] = "size";
    return roles;
}
}
