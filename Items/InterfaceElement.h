#ifndef INTERFACEELEMENT_H
#define INTERFACEELEMENT_H
#include "Item.h"

namespace Uber {
    class Inlet;
    class Outlet;
    class InletObjectListModel;
    class OutletObjectListModel;
    class InterfaceElement : public Item
    {
        Q_OBJECT
        Q_PROPERTY( QString name READ getName WRITE setName NOTIFY nameChanged )
    public:
        InterfaceElement();
        virtual ~InterfaceElement();
        void                                        setName( QString name );
        Q_INVOKABLE QString                         getName();
        // It seems that the QT mocing has a bug and requires to use the namespace in the return type.
        // More here: http://stackoverflow.com/questions/14086289/use-c-slot-in-qml-which-returns-type-in-namespace
        Q_INVOKABLE Uber::InletObjectListModel*     getInletModel() const;
        Q_INVOKABLE Uber::OutletObjectListModel*    getOutletModel() const;

        Q_INVOKABLE int                             getNumberOfInlets();
        Q_INVOKABLE int                             getNumberOfOutlets();
        void                                        appendInlet(Inlet *inlet);
        void                                        appendOutlet(Outlet *outlet);
    signals:
        void                                        nameChanged();
    public slots:
    protected:
    private:
        QString                                     m_Name;
        InletObjectListModel*                       m_InletModel;
        OutletObjectListModel*                      m_OutletModel;
        virtual void                                initialize() = 0;
    };
}
#endif // INTERFACEELEMENT_H
