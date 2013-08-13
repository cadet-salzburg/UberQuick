#ifndef PAINTERBEZIER_H
#define PAINTERBEZIER_H

#include <QQuickPaintedItem>
#include <QPainterPath>

namespace Uber {
class PainterBezier : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF p1 READ p1 WRITE setP1 NOTIFY p1Changed)
    Q_PROPERTY(QPointF p2 READ p2 WRITE setP2 NOTIFY p2Changed)
    Q_PROPERTY(QPointF p3 READ p3 WRITE setP3 NOTIFY p3Changed)
    Q_PROPERTY(QPointF p4 READ p4 WRITE setP4 NOTIFY p4Changed)
    Q_PROPERTY(QColor outlineColor READ getOutlineCol WRITE setOutlineCol NOTIFY outlineColChanged )
    Q_PROPERTY(QColor fillColor READ getFillCol WRITE setFillCol NOTIFY fillColChanged )
    Q_PROPERTY(qreal fillWidth READ getFillWidth WRITE setFillWidth NOTIFY fillWidthChanged )
    Q_PROPERTY(qreal outlineWidth READ getOutlineWidth WRITE setOutlineWidth NOTIFY outlineWidthChanged )
public:
    explicit        PainterBezier(QQuickItem  *parent = 0);
    void            paint(QPainter * painter);

    QPointF         p1() const { return m_p1; }
    QPointF         p2() const { return m_p2; }
    QPointF         p3() const { return m_p3; }
    QPointF         p4() const { return m_p4; }

    void            setP1(const QPointF &p);
    void            setP2(const QPointF &p);
    void            setP3(const QPointF &p);
    void            setP4(const QPointF &p);

    QColor          getOutlineCol() const;
    void            setOutlineCol( const QColor& color );

    QColor          getFillCol() const;
    void            setFillCol( const QColor& color );

    qreal           getOutlineWidth() const;
    void            setOutlineWidth( qreal width );

    qreal           getFillWidth() const;
    void            setFillWidth( qreal width );

private:
    QPainterPath    m_Path;
    QPointF         m_p1;
    QPointF         m_p2;
    QPointF         m_p3;
    QPointF         m_p4;
    QColor          m_OutlineColor;
    QColor          m_FillColor;
    qreal           m_OutlineWidth;
    qreal           m_FillWidth;
    void            calculateBezierParameters(QPointF &a, QPointF &b, QPointF &c, QPointF &d);
    QRectF          calculateBoundingBox();
    QPointF         calculateDiscriminant(const QPointF &a, const QPointF &b, const QPointF &c);
    int             getNumberOfMaxima(const QPointF& det );

signals:
    void            p1Changed(const QPointF &p);
    void            p2Changed(const QPointF &p);
    void            p3Changed(const QPointF &p);
    void            p4Changed(const QPointF &p);
    void            outlineColChanged(const QColor& color);
    void            fillColChanged(const QColor& color);
    void            outlineWidthChanged(qreal width);
    void            fillWidthChanged(qreal width);

public slots:
    void            updatePath();

};
}
#endif // PAINTERBEZIER_H
