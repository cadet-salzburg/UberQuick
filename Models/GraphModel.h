#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QAbstractListModel>

class GraphModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GraphModel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GRAPHMODEL_H
