#include "DockModel.h"

namespace Uber {
    DockModel::DockModel(QObject *parent)
    :QAbstractListModel(parent)
    {

    }

    int DockModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return count();
    }

    QVariant DockModel::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= count())
            return QVariant();
        if (role ==  PathRole )
        {
            return QVariant::fromValue(m_Entries.at(index.row()).getIconUrl());
        }
        else if (role == NameRole)
        {
            return QVariant::fromValue(m_Entries.at(index.row()).getBlockName());
        }
        return QVariant();
    }

    void DockModel::addEntry(const GridEntry &entry )
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_Entries << entry;
        endInsertRows();
        emit countChanged();
    }

    void DockModel::addEntries(const GridEntryList &entries)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        for ( GridEntryList::const_iterator iter = entries.constBegin(); iter!=entries.constEnd(); ++iter )
        {
            m_Entries << *iter;
        }
        endInsertRows();
        emit countChanged();
    }
    inline int DockModel::count() const
    {
        return m_Entries.count();
    }

    QHash<int,QByteArray> DockModel::roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[PathRole] = "path";
        roles[NameRole] = "name";
        return roles;
    }
}
