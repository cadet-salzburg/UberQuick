#include "EventFilter.h"
#include <QDebug>

namespace Uber {

    EventFilter::EventFilter(QObject *parent)
    :QObject(parent)
    {
        qDebug() << "EventFilter constructor called.";
        if ( hasParent() )
        {
            QObject::parent()->installEventFilter(this);
            qDebug() << "Has parent and! has set up the event filter";
        }
    }

    void EventFilter::setMouseEvent( int type )
    {
        m_EventType = type;
    }

    bool EventFilter::eventFilter(QObject *obj, QEvent *e)
    {
//    return false;
//    if( e->type() == QEvent::MouseButtonPress )
//    {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
//        emit activated();
//    }
        qDebug() << "Event filter called.";
        return true;
        //return QObject::eventFilter(obj, e);
    }
}
