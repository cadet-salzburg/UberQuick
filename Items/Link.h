#ifndef LINK_H
#define LINK_H
#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"
#include <QVector>
#include <QDebug>
#include <QObjectList>
#include "StringModel.h"
#include <memory>
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"
#include <QMutex>
#include <QImage>
#include <QMutex>
#include "../system/System.h"

namespace Uber {
using namespace _2Real;
using namespace _2Real::app;
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

        void                                connectSignals();
        void                                receivedData( std::shared_ptr<const _2Real::CustomType> data );

    protected:

    signals:
        void                    linkChanged();

    public slots:
        void    slotCall()
        {
            qDebug() << " The Slot Was Called ";
        }
//        void killSelf()
//        {
//            System::getInstance()->removeItem(this);
//        }

    private:
        Inlet*                                      m_Inlet;
        Outlet*                                     m_Outlet;
        QObjectList                                 m_Points;
        StringModel*                                m_ConnectionOptions;
        QMutex                                      m_Mutex;
        //std::shared_ptr<const _2Real::CustomType>   m_Data;
    };
    typedef QSharedPointer<Link> LinkRef;
    QDebug operator<<(QDebug dbg, const Link &link);
}
#endif // LINK_H
