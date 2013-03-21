#ifndef BLOCKMODEL_H
#define BLOCKMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "../Items/Block.h"

namespace Uber {
    class Inlet;
    class Outlet;
    class BlockModel : public QAbstractListModel
    {
        Q_OBJECT
    public:
        enum ModelRoles {
            ModelTypeRole = Qt::UserRole + 1,
            NameRole      = ModelTypeRole + 1,
            DimRole
        };
        explicit BlockModel(QObject *parent = 0);
        ~BlockModel();
        virtual int             rowCount(const QModelIndex & parent = QModelIndex()) const;
        virtual QVariant        data(const QModelIndex & index, int role = Qt::DisplayRole) const;

        void                    addEntry( Block* block);

        int                     count() const;

    private:
    signals:
        void                    countChanged();
    public slots:
    protected:
        QList<Block*>           m_Entries;
    };
}
#endif // BLOCKMODEL_H
