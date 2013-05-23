#ifndef LINK_H
#define LINK_H
#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"
#include <QVector>
#include <QDebug>
#include <QObjectList>

namespace Uber {
    class Point : public QObject {
        Q_OBJECT
    public:
        Point( QPointF p = QPointF() );
        Q_INVOKABLE QPointF     get() const;
        Q_INVOKABLE void        set( const QPointF &p );
        Q_INVOKABLE qreal       getX() const;
        Q_INVOKABLE void        setX( const qreal &x );
        Q_INVOKABLE qreal       getY() const;
        Q_INVOKABLE void        setY( const qreal &y );
    private:
        QPointF m_Point;
    };
    class Link : public Item
    {
        Q_OBJECT
    public:
        Link();
        void                                setInlet( Inlet *inlet );
        void                                setOutlet( Outlet *outlet );

        Q_INVOKABLE     void                addPoint( const QPointF &p );
        Q_INVOKABLE     QObjectList         getPoints();

        Q_INVOKABLE     QPointF             getStartPos();
        Q_INVOKABLE     QPointF             getEndPos();
        Q_INVOKABLE     void                updateEndPosition( const QPointF& point );
    protected:


    private:
        Inlet*                              m_Inlet;
        Outlet*                             m_Outlet;
        QObjectList                         m_Points;

    };
    typedef QSharedPointer<Link> LinkRef;
    QDebug operator<<(QDebug dbg, const Link &link);
}
#endif // LINK_H
