#ifndef EVENTFILTER_H
#define EVENTFILTER_H
#include <QObject>
#include <QEvent>
#include <QMouseEvent>

namespace Uber {
class EventFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QObject* parent READ parent WRITE setParent NOTIFY parentChanged )
    Q_PROPERTY( int type READ getMouseEvent WRITE setMouseEvent NOTIFY mouseEventChanged )
public:
    EventFilter(QObject *parent = 0);
    void    setMouseEvent( int type);
    int     getMouseEvent(){ return m_EventType; }

    Q_INVOKABLE bool hasParent()
    {
        bool result = false;
        if ( QObject::parent() )
        {
             QObject::parent()->installEventFilter(this);
             result = true;
        } else
        {
            result = false;
        }
        return result;
    }

    bool    eventFilter(QObject *obj, QEvent *e);
signals:
    void parentChanged();
    void mouseEventChanged();
    void activated();
public slots:
private:
    int m_EventType;
};
}
#endif // EVENTFILTER_H
