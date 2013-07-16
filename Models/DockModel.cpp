#include "DockModel.h"
#include "../items/Block.h"
#include "../items/Slider.h"
#include "../items/TextIO.h"
#include <QStringListModel>

namespace Uber {
    DockModel::DockModel(QObject *parent)
    :QAbstractListModel( parent )
    ,m_AutoCompleter( nullptr )
    {
        m_AutoCompleter = new QCompleter(this);
        m_AutoCompleter->setModel(this);
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
        else if (role == NameRole  || role == Qt::EditRole )
        {
            return QVariant::fromValue(m_Entries.at(index.row()).getName());
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

    QAbstractItemModel* DockModel::getCompletionModel(const QString &text)
    {
        m_AutoCompleter->setCompletionPrefix("");
        m_AutoCompleter->setCompletionMode(QCompleter::PopupCompletion);
        QAbstractItemModel *md = m_AutoCompleter->completionModel();
        //QSortFilterProxyModel *actualMd = qobject_cast<QSortFilterProxyModel*>(md);
        QStringListModel *actualMd = new QStringListModel(md);
        return actualMd;
    }

    GridEntry   DockModel::getEntry( int row )
    {
        if ( m_Entries.size() >= row+1)
        {
            return m_Entries.at(row);
        } else {
            return GridEntry();
        }
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

    Item *DockModel::create( int row )
    {
        Item *item = nullptr;
        if ( row < rowCount() )
        {
            GridEntry entry = getEntry(row);
            if ( entry.typeIs(BlockType) )
            {
                BlockHandle handle = entry.getBundleHandle().createBlockInstance(entry.getName().toUtf8().constData());
                item = new Block(handle, entry.getName());
            } else if ( entry.typeIs(SliderType) )
            {
                item = new Slider();
            } else if ( entry.typeIs(TextInputType) )
            {
                item = new TextIO();
            }
        }
        return item;
    }
}
