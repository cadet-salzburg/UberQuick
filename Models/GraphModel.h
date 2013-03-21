#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include "BlockModel.h"

namespace Uber {
    class GraphModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(int count READ count NOTIFY countChanged)
    public:
        enum ModelRoles {
            ModelTypeRole = Qt::UserRole + 1,
            NameRole      = ModelTypeRole + 1,
            DimRole
        };
    explicit                                    GraphModel(QObject *parent = 0);
        int                                     rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant                                data(const QModelIndex & index, int role = Qt::DecorationRole) const;
        void                                    addEntry( Item* entry );
        int                                     count() const;
        QHash<int,QByteArray>                   roleNames() const;
    signals:
        void                                    countChanged();
    public slots:

    private:
        QList< QPair< QPersistentModelIndex, QString> >   m_Entries;
        BlockModel                              m_BlockModel;

    };
}
#endif // GRAPHMODEL_H
