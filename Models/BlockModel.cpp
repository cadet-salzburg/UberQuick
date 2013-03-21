#include "BlockModel.h"
#include"../Items/Inlet.h"
#include "../Items/Outlet.h"

namespace Uber {
    BlockModel::BlockModel(QObject *parent)
    :QAbstractListModel(parent)
    {

    }

    BlockModel::~BlockModel()
    {

    }

    int BlockModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return count();
    }

    QVariant BlockModel::data(const QModelIndex &index, int role) const
    {
        if ( role==NameRole)
        {
            return QVariant::fromValue( m_Entries.at(index.row())->getName() );
        }
       //return QVariant::fromValue(m_Entries.at(index.row()));
    }

    void BlockModel::addEntry(Block *block)
    {
//        beginInsertRows(QModelIndex(), m_Entries.count(), m_Entries.count());
        m_Entries.push_back(block);
        emit countChanged();
//        endInsertRows();
    }

    int BlockModel::count() const
    {
        return m_Entries.count();
    }
}
