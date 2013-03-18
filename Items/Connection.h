#ifndef CONNECTION_H
#define CONNECTION_H

#include <QQuickItem>

namespace Uber {
    class Connection : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QPointF p1 READ p1 WRITE setP1 NOTIFY p1Changed)
        Q_PROPERTY(QPointF p2 READ p2 WRITE setP2 NOTIFY p2Changed)
        Q_PROPERTY(QPointF p3 READ p3 WRITE setP3 NOTIFY p3Changed)
        Q_PROPERTY(QPointF p4 READ p4 WRITE setP4 NOTIFY p4Changed)
        Q_PROPERTY(int segmentCount READ segmentCount WRITE setSegmentCount NOTIFY segmentCountChanged)
    public:
        Connection( QQuickItem *parent = 0 );
        ~Connection();
        QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

        QPointF p1() const { return m_p1; }
        QPointF p2() const { return m_p2; }
        QPointF p3() const { return m_p3; }
        QPointF p4() const { return m_p4; }

        int segmentCount() const { return m_segmentCount; }

        void setP1(const QPointF &p);
        void setP2(const QPointF &p);
        void setP3(const QPointF &p);
        void setP4(const QPointF &p);

        void setSegmentCount(int count);
    signals:
        void p1Changed(const QPointF &p);
        void p2Changed(const QPointF &p);
        void p3Changed(const QPointF &p);
        void p4Changed(const QPointF &p);

        void segmentCountChanged(int count);

    private:

        QPointF m_p1;
        QPointF m_p2;
        QPointF m_p3;
        QPointF m_p4;

        int m_segmentCount;
    };
}
#endif // CONNECTION_H
