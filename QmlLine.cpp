#include "QmlLine.h"
#include <QSGGeometryNode>
namespace Uber {
    QmlLine::QmlLine(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Width(5)
    ,m_Thickness(5.f)
    ,m_Color(Qt::blue)
    ,m_Geometry(QSGGeometry::defaultAttributes_Point2D(), 2)
    {
        setFlag(ItemHasContents);
        m_Material.setColor(m_Color);
        m_Geometry.setDrawingMode(GL_LINES);
        m_Geometry.setLineWidth(m_Thickness);

    }

    void QmlLine::setWidth(float width)
    {
        if ( width != m_Width )
        {
            m_Width = width;
            emit widthChanged();
        }
    }

    float QmlLine::getWidth() const
    {
        return m_Width;
    }

    void QmlLine::setThickness( float thickness )
    {
        if ( thickness!=m_Thickness)
        {
            m_Thickness = thickness;
            m_Geometry.setLineWidth(m_Thickness);
            emit thicknessChanged();
        }
    }

    float QmlLine::getThickness( ) const
    {
        return m_Thickness;
    }

    void QmlLine::setColor(const QColor &color)
    {
        if ( color != m_Color )
        {
            m_Color = color;
            m_Material.setColor(color);
            emit colorChanged();
        }
    }

    QColor QmlLine::getColor() const
    {
        return m_Color;
    }

    QSGNode* QmlLine::updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData )
    {
        QSGGeometryNode *node = static_cast<QSGGeometryNode *>(oldNode);
        if (!node)
        {
            node = new QSGGeometryNode();
        }
        QSGGeometry::Point2D *v = m_Geometry.vertexDataAsPoint2D();
        QPointF p = position();
        v[0].x = p.x() - m_Width/2.f;
        v[0].y = p.y();
        v[1].x = p.x() + m_Width/2.f;
        v[1].y = p.y();
        node->setGeometry(&m_Geometry);
        node->setMaterial(&m_Material);
        return node;
    }
}
