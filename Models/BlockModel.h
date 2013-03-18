#ifndef BLOCKMODEL_H
#define BLOCKMODEL_H

#include <QAbstractItemModel>

namespace Uber {
    class Inlet;
    class Outlet;
    class BlockModel : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        explicit BlockModel(QObject *parent = 0);
        ~BlockModel();
        virtual int             columnCount(const QModelIndex & parent = QModelIndex()) const;
        virtual QVariant        data(const QModelIndex & index, int role = Qt::DisplayRole) const;
        virtual QModelIndex     index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
        virtual QModelIndex     parent(const QModelIndex & index ) const;
        virtual int             rowCount(const QModelIndex & parent = QModelIndex()) const;

        QList<Inlet>            getInlets() const;
        QList<Outlet>           getOutlets() const;
        void                    setPosition( const QPoint &pos );
        QPoint                  getPosition() const;
    private:
    signals:
    public slots:
    };
}
#endif // BLOCKMODEL_H
