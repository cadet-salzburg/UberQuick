#include "StringModel.h"
#include "../Items/StringObject.h"
namespace Uber {
    StringModel::StringModel(QObject *parent)
    :QObjectListModelT<StringObject*>(parent)
    {

    }
    StringModel::StringModel(const QList<StringObject*> &objects, QObject *parent)
    :QObjectListModelT<StringObject*>(objects,parent)
    {

    }
    StringModel::StringModel(StringModel *stringModel, QObject *parent)
    :QObjectListModelT<StringObject*>(stringModel,parent)
    {

    }
    QVariant StringModel::data(const QModelIndex &index, int role ) const
    {
        if (index.row() < 0 || index.row() >= m_objects.size())
        {
            return QVariant();
        } else {
            return QVariant::fromValue(m_objects.at(index.row()));
        }
    }
}
