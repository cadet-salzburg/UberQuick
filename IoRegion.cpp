#include "IoRegion.h"
#include <QSGGeometryNode>
#include <qmath.h>
#include <QPainterPathStroker>
namespace Uber {
    IoRegion::IoRegion(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Geometry( QSGGeometry::defaultAttributes_Point2D(), 18)
    {
        setFlag(ItemHasContents);
        setEnabled(true);
        setAcceptedMouseButtons(Qt::AllButtons);
        m_Geometry.setDrawingMode(GL_TRIANGLE_FAN);
        m_Material.setColor(Qt::red);
        setZ(0);
    }

    QColor IoRegion::getColor() const
    {
        return m_Material.color();
    }

    void IoRegion::setColor( const QColor &color)
    {
        m_Material.setColor(color);
        //update();
    }

    float IoRegion::getRadius() const
    {
        return m_Radius;
    }

    void IoRegion::setRadius( const float &radius )
    {
        m_Radius = radius;
        setWidth(2*m_Radius);
        setHeight(2*m_Radius);
    }

    QSGNode *IoRegion::updatePaintNode(QSGNode *n, UpdatePaintNodeData *d)
    {
        QSGGeometryNode *node = static_cast<QSGGeometryNode*>(n);
        if (!node) node = new QSGGeometryNode();
        QSGGeometry::Point2D *v = m_Geometry.vertexDataAsPoint2D();
        const QRectF rect = boundingRect();
        QPointF center = rect.center();
        float   radius = rect.width()/2.f;
        int numPoints = m_Geometry.vertexCount();
        v[0].x = center.x();
        v[0].y = center.y();
        for ( int i=1;  i < numPoints; ++i )
        {
            float theta = i*2*M_PI/( numPoints - 2 );
            v[i].x = center.x() + radius*cos(theta);
            v[i].y = center.y() - radius*sin(theta);
        }

        node->setGeometry(&m_Geometry);
        node->setMaterial(&m_Material);
        return node;
    }
}
