#ifndef LINK_H
#define LINK_H

#include <QObject>
#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"

namespace Uber {
    class Link : public Item
    {
        Q_OBJECT
    public:
        Link(QObject *parent = nullptr);
        Link( Inlet *inlet, Outlet *outlet, QObject *parent = nullptr );
        Link( const Link &other);
        Inlet*      getInlet() const;
        Outlet*     getOutlet() const;
        void        link();
        void        unlink();
    private:
        Inlet       *m_Inlet;
        Outlet      *m_Outlet;
    signals:
    public slots:
    };
}
#endif // LINK_H
