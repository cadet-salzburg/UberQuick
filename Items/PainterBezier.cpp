#include "PainterBezier.h"
#include <QPainter>
#include <QPen>
#include <QPolygon>
namespace Uber {
PainterBezier::PainterBezier(QQuickItem  *parent)
:QQuickPaintedItem (parent)
,m_p1(QPointF(0.f,0.f))
,m_p2(QPointF(0.f,0.f))
,m_p3(QPointF(0.f,0.f))
,m_p4(QPointF(0.f,0.f))
,m_OutlineColor(Qt::black)
,m_FillColor(QColor(177,189,180))
,m_OutlineWidth(1.f)
,m_FillWidth(3.f)
{
    setX(0);
    setY(0);
    setWidth(1);
    setHeight(1);
    setFlag(ItemHasContents, true);
    //setAntialiasing(true);
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setSmooth(true);
}

void PainterBezier::setP1(const QPointF &p)
{
    if (p == m_p1)
        return;
    m_p1 = p;
    emit p1Changed(p);
    update();
}

void PainterBezier::setP2(const QPointF &p)
{
    if (p == m_p2)
        return;
    m_p2 = p;
    emit p2Changed(p);
    update();
}
void PainterBezier::setP3(const QPointF &p)
{
    if (p == m_p3)
        return;

    m_p3 = p;
    emit p3Changed(p);
    update();
}
void PainterBezier::setP4(const QPointF &p)
{
    if (p == m_p4)
        return;

    m_p4 = p;
    emit p4Changed(p);
    update();
}

QColor PainterBezier::getOutlineCol() const
{
    return m_OutlineColor;
}

void PainterBezier::setOutlineCol(const QColor &color)
{
    if ( m_OutlineColor != color )
    {
        m_OutlineColor = color;
        update();

    }
}

QColor PainterBezier::getFillCol() const
{
    return m_FillColor;
}

void PainterBezier::setFillCol(const QColor &color)
{
    if ( m_FillColor != color )
    {
        m_FillColor = color;
        update();
    }
}

qreal PainterBezier::getOutlineWidth() const
{
    return m_OutlineWidth;
}

void PainterBezier::setOutlineWidth(qreal width)
{
    if ( m_OutlineWidth != width )
    {
        m_OutlineWidth = width;
        update();
    }
}

qreal PainterBezier::getFillWidth() const
{
    return m_FillWidth;
}

void PainterBezier::setFillWidth(qreal width)
{
    if ( m_FillWidth != width )
    {
        m_FillWidth = width;
        update();
    }
}

void PainterBezier::calculateBezierParameters(QPointF &a, QPointF &b, QPointF &c, QPointF &d)
{
    // A Bezier f(t) = a*t^3 + b*t^2 + c*t + d     (where t is a vector going from (0,0) to (1,1) )
    a = m_p4 - 3*m_p3 + 3*m_p2 - m_p1;
    b = 3*m_p3-6*m_p2+3*m_p1;
    c = 3*m_p2-3*m_p1;
    d = m_p1;
}
QPointF PainterBezier::calculateDiscriminant(const QPointF &a, const QPointF &b, const QPointF &c)
{
    // D = b^2 - 4ac
    // A Bezier f(t) = a*t^3 + b*t^2 + c*t + d   where t is a vector
    // with: d = m_p1
    //       c = 3*m_p2-3*m_p1
    //       b = 3*m_p3-6*m_p2+3*m_p1
    //       a =  m_p4-3*m_p3+3*m_p2-m_p1

    // 1st Derivative:   f'(t) = 3*a*t^2 + 2*b*t + c is a quadratic.
    qreal Dx = 4.*b.x()*b.x() - 12.*a.x()*c.x();
    qreal Dy = 4.*b.y()*b.y() - 12.*a.y()*c.y();
    return QPointF(Dx, Dy);
}

QRectF PainterBezier::calculateBoundingBox()
{
//    //f'(t) = 3*a*t^2 + 2*b*t + c  ( At^2 + Bx + C )
//    QPointF a,b,c,d;
//    calculateBezierParameters(a,b,c,d);
//    QPointF det = calculateDiscriminant(a,b,c);
//    int numMaxima = getNumberOfMaxima(det);
//    qDebug() << "Num Maxima from func: " << numMaxima;
//    QVector<QPointF> m_Roots;
//    int mult = 1;
//    QPointF A = 3*a;
//    QPointF B = 2*b;
//    QPointF C = c;
//    if ( A.x()!= 0 && A.y() != 0 )
//    {
//        for ( int roots = 0; roots < numMaxima; ++roots )
//        {
//            qreal RootX  = ( -B.x() + mult*sqrt(B.x()*B.x() - 4*A.x()*C.x()) )/2/A.x();
//            qreal RootY  = ( -B.y() + mult*sqrt(B.y()*B.y() - 4*A.y()*C.y()) )/2/A.y();
//            if ( RootX >= 0 && RootX <= 1 && RootY >= 0 && RootY <= 1 )
//            {
//                m_Roots.push_back(QPointF(RootX, RootY));
//            } else {
//                qDebug() << "not inr";
//            }
//            mult*=-1;
//        }
//    } else {
//        qDebug() << "Zero";
//    }
    QVector<QPointF> m_Roots;
    m_Roots.push_back(m_p1);
    m_Roots.push_back(m_p2);
    m_Roots.push_back(m_p3);
    m_Roots.push_back(m_p4);

    QPolygon polygon(m_Roots.size()); //= QPolygon(m_Roots);
    for ( int i = 0; i< m_Roots.size(); ++i )
    {
        polygon.setPoint(i, m_Roots[i].toPoint());
    }
    return polygon.boundingRect();
}




void PainterBezier::paint(QPainter * painter)
{
    painter->setBrush(Qt::transparent);
    QRectF rect = calculateBoundingBox();
    setX(rect.topLeft().x() - 10);
    setY( rect.topLeft().y() - 10);
    setWidth( rect.width() + 20);
    setHeight( rect.height() + 20);
    QPen pen;
    pen.setWidthF(m_OutlineWidth);
    pen.setBrush(m_OutlineColor);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->setPen(pen);
    painter->setBrush(m_FillColor);
    QPainterPath bezierPath;
    QPointF pos(x(),y());
    bezierPath.moveTo(m_p1 - pos);
    bezierPath.cubicTo( m_p2 - pos, m_p3 - pos, m_p4 - pos );
    QPainterPathStroker outliner;
    outliner.setWidth(m_FillWidth);
    outliner.setCapStyle( Qt::FlatCap );
    m_Path = outliner.createStroke(bezierPath);
    painter->drawPath(m_Path);
}

void PainterBezier::updatePath()
{
    QPainterPath bezierPath;
    bezierPath.moveTo(m_p1);
    bezierPath.cubicTo( m_p2, m_p3, m_p4 );
    QPainterPathStroker outliner;
    outliner.setWidth(m_FillWidth);
    outliner.setCapStyle( Qt::FlatCap );
    m_Path = outliner.createStroke(bezierPath);
}
}
