#ifndef INLETOBJECTLISTMODEL_H
#define INLETOBJECTLISTMODEL_H

#include "QObjectListModelT.h"

namespace Uber {
    class BaseInlet;
    class InletObjectListModel : public QObjectListModelT<BaseInlet*>
    {
        Q_OBJECT
    public:
        InletObjectListModel(QObject *parent = nullptr);
        InletObjectListModel(const QList<BaseInlet*> &objects, QObject *parent = 0);
        InletObjectListModel(InletObjectListModel *inletListModel, QObject *parent);
        virtual ~InletObjectListModel();
    };
}
#endif // INLETOBJECTLISTMODEL_H
