#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QObject>
#include <QMap>

namespace Uber {
    class QAbstractItemModel;
    class Workbench : public QObject
    {
        Q_OBJECT
    public:
        Workbench(QObject *parent = 0);
    private:
        QMap<QString, QAbstractItemModel* > m_Models;
    signals:
    public slots:
    };
}
#endif // WORKBENCH_H
