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
        Q_UNUSED(role)
        return QVariant::fromValue(m_Entries.at(index.row()));
    }

    void BlockModel::addEntry(Block *block)
    {
        m_Entries.push_back(block);
        emit countChanged();
    }

    int BlockModel::count() const
    {
        return m_Entries.count();
    }
}
