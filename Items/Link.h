#ifndef LINK_H
#define LINK_H
#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"
#include <QDebug>

namespace Uber {
    class Link : public Item
    {
        Q_OBJECT
    public:
        Link();
        void                    setInlet( Inlet *inlet );
        void                    setOutlet( Outlet *outlet );
        Q_INVOKABLE     QPointF getStartPos();
        Q_INVOKABLE     QPointF getEndPos();
        Q_INVOKABLE     void    updateEndPosition( const QPointF& point );
    private:
        Inlet*          m_Inlet;
        Outlet*         m_Outlet;
        QPointF         m_EndPos;
    };
    typedef QSharedPointer<Link> LinkRef;
    QDebug operator<<(QDebug dbg, const Link &link);
}
#endif // LINK_H
