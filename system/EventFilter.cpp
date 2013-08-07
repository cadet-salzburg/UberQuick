#include "EventFilter.h"
#include <QDebug>

namespace Uber {

    EventFilter::EventFilter(QObject *parent)
    :QObject(parent)
    {
        if ( hasParent() )
        {
            QObject::parent()->installEventFilter(this);
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
        //qDebug() << "Event filter called.";
        return true;
        //return QObject::eventFilter(obj, e);
    }
}
