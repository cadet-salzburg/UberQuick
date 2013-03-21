#include "GraphModel.h"

namespace Uber {
    GraphModel::GraphModel(QObject *parent)
    :QAbstractListModel(parent)
    {

    }

    int GraphModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent)
        return count();
    }

    QVariant GraphModel::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= count())
            return QVariant();
        if ( role == ModelTypeRole )
        {
            return  m_Entries[index.row()].second;
        }
        if ( m_Entries[index.row()].second == "Uber::Block" )
        {
            return m_BlockModel.data( m_Entries[index.row()].first, role);
        }
        return QVariant();
    }

    void GraphModel::addEntry(Item *entry)
    {
        if ( entry->getClassName()=="Uber::Block")
        {
            beginInsertRows(QModelIndex(), m_Entries.count(), m_Entries.count() );
            int row = m_BlockModel.count();
            m_BlockModel.addEntry(dynamic_cast<Block*>(entry));
            m_Entries.push_back(qMakePair(QPersistentModelIndex(m_BlockModel.index(row)),QString("Uber::Block")));
            endInsertRows();
            emit countChanged();
        }
    }

    int GraphModel::count() const
    {
        return m_Entries.count();
    }

    QHash<int,QByteArray> GraphModel::roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[ModelTypeRole] = "modeltype";
        roles[NameRole] = "name";
        roles[DimRole] = "size";
        return roles;
    }
}
