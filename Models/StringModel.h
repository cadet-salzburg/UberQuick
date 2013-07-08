#ifndef STRINGMODEL_H
#define STRINGMODEL_H
#include "QObjectListModelT.h"
#include "../Items/StringObject.h"

namespace Uber {
    class StringModel : public QObjectListModelT<StringObject*>
    {
        Q_OBJECT
    public:
        StringModel(QObject *parent = nullptr);
        StringModel(const QList<StringObject*> &objects, QObject *parent = 0);
        StringModel(StringModel *stringModel, QObject *parent);
        QVariant data( const QModelIndex &index, int role ) const;
    };
    typedef QSharedPointer<StringModel> StringModelRef;
}
#endif // STRINGMODEL_H
