#include "BlockModel.h"
#include"../Items/Inlet.h"
#include "../Items/Outlet.h"

namespace Uber {
    BlockModel::BlockModel(QObject *parent)
    :QAbstractItemModel(parent)
    {

    }
    BlockModel::~BlockModel()
    {
    }

    int BlockModel::columnCount(const QModelIndex &parent) const
    {
        return 0;
    }

    QVariant BlockModel::data(const QModelIndex &index, int role) const
    {
        return 0;
    }

    QModelIndex BlockModel::index(int row, int column, const QModelIndex &parent) const
    {
        return QModelIndex();
    }

    QModelIndex BlockModel::parent(const QModelIndex &index) const
    {
        return QModelIndex();
    }

    int BlockModel::rowCount(const QModelIndex &parent) const
    {
        return 0;
    }

    QList<Inlet> BlockModel::getInlets() const
    {
        return QList<Inlet>();
    }

    QList<Outlet> BlockModel::getOutlets() const
    {
        return QList<Outlet>();
    }

    void BlockModel::setPosition(const QPoint &pos)
    {
    }

    QPoint BlockModel::getPosition() const
    {
        return QPoint();
    }
}
