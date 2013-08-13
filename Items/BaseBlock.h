#ifndef BASEBLOCK_H
#define BASEBLOCK_H
#include <QDebug>
#include "Item.h"
namespace Uber {
    class InletObjectListModel;
    class OutletObjectListModel;
    class BaseBlock : public Item
    {
        Q_OBJECT
    public:
        explicit BaseBlock(QObject *parent = 0);
        virtual ~BaseBlock();
        // It seems that the QT mocing has a bug and requires to use the namespace in the return type.
        // More here: http://stackoverflow.com/questions/14086289/use-c-slot-in-qml-which-returns-type-in-namespace
        Q_INVOKABLE Uber::InletObjectListModel*     getInletModel() const;
        Q_INVOKABLE Uber::OutletObjectListModel*    getOutletModel() const;
        Q_INVOKABLE int                             getNumberOfInlets();
        Q_INVOKABLE int                             getNumberOfOutlets();
    public:
        InletObjectListModel*                       m_InletModel;
        OutletObjectListModel*                      m_OutletModel;
        virtual void                                initialize() = 0;
    signals:

    public slots:
    };
}
#endif // BASEBLOCK_H
