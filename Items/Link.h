#ifndef LINK_H
#define LINK_H
#include <memory>
#include <QMutex>
#include <QObjectList>
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"
#include "Item.h"
namespace Uber {
    using namespace _2Real;
    class Item;
    class Inlet;
    class Outlet;
    class StringModel;
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
        virtual ~Link();
        void                                setInlet( Inlet *inlet );
        void                                setOutlet( Outlet *outlet );
        Inlet*                              getInlet();
        Outlet*                             getOutlet();

        Q_INVOKABLE     void                addPoint( const QPointF &p );
        Q_INVOKABLE     QObjectList         getPoints();

        Q_INVOKABLE     QPointF             getStartPos();
        Q_INVOKABLE     QPointF             getEndPos();
        Q_INVOKABLE     void                updatePosition( const QPointF& pos );
        bool                                isValid();
        StringModel*                        getConnectionTypename();
        StringModel*                        getConnectionOptions();

        virtual void                        connectSignals();
        virtual void                        disconnectSignals();
        void                                receivedData( std::shared_ptr<const CustomType> data );

    protected:

    signals:
        void                                linkChanged();

    public slots:
        void    slotCall()
        {

        }

    private:
        Inlet*                                      m_Inlet;
        Outlet*                                     m_Outlet;
        QObjectList                                 m_Points;
        StringModel*                                m_ConnectionOptions;
        QMutex                                      m_Mutex;
    };
}
#endif // LINK_H
