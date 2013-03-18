#ifndef DATAFLOWMODEL_H
#define DATAFLOWMODEL_H

#include <QAbstractListModel>
#include "../Items/Item.h"


#include <QAbstractListModel>
#include <QList>
#include <QSize>
#include <QUrl>
#include <QDebug>

namespace Uber {

    typedef QList<Item*> ItemList;

    class DataflowModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int count READ count NOTIFY countChanged)
    public:
        enum ModelRoles {
            ModelTypeRole = Qt::UserRole + 1,
            DimRole
        };
        explicit                DataflowModel(QObject *parent = 0);
        int                     rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant                data(const QModelIndex & index, int role = Qt::DecorationRole) const;

        void                    addEntry( Item* entry );

        int                     count() const;
        QHash<int,QByteArray>   roleNames() const;
    signals:
        void                    countChanged();
    public slots:
    private:
        ItemList                m_Entries;
    };
}
#endif // DOCKMODEL_H
