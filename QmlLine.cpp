#include "QmlLine.h"
#include <QSGGeometryNode>
namespace Uber {
    QmlLine::QmlLine(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Thickness(5.f)
    ,m_Color(Qt::blue)
    ,m_Geometry(QSGGeometry::defaultAttributes_Point2D(), 2)
    ,m_SegmentCount(2)
    {
        setFlag(ItemHasContents, true);
        m_Material.setColor(m_Color);
                m_Geometry.setLineWidth(10);
        m_Geometry.setDrawingMode(GL_LINES);
        //m_Geometry.setLineWidth(m_Thickness);

    }

    void QmlLine::setThickness( float thickness )
    {
        if ( thickness!=m_Thickness)
        {
            m_Thickness = thickness;
            m_Geometry.setLineWidth(m_Thickness);
            emit thicknessChanged();
            update();
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
            update();
        }
    }

    QColor QmlLine::getColor() const
    {
        return m_Color;
    }

    QSGNode* QmlLine::updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData )
    {
        QSGGeometryNode *node = 0;
        QSGGeometry *geometry = 0;

        if (!oldNode) {
            node = new QSGGeometryNode;
            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_SegmentCount);
            geometry->setLineWidth(10);
            geometry->setDrawingMode(GL_LINES);
            node->setGeometry(geometry);
            node->setFlag(QSGNode::OwnsGeometry);
            //QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
            //material->setColor(QColor(255, 0, 0));
            node->setMaterial(&m_Material);
            //node->setFlag(QSGNode::OwnsMaterial);
        } else {
            node = static_cast<QSGGeometryNode *>(oldNode);
            geometry = node->geometry();
            geometry->allocate(m_SegmentCount);
        }

        QRectF bounds = boundingRect();
        QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
//        for (int i = 0; i < m_segmentCount; ++i) {
//            qreal t = i / qreal(m_SegmentCount - 1);
//            qreal invt = 1 - t;

//            QPointF pos = invt * invt * invt * m_p1
//                        + 3 * invt * invt * t * m_p2
//                        + 3 * invt * t * t * m_p3
//                        + t * t * t * m_p4;

//            float x = bounds.x() + pos.x() * bounds.width();
//            float y = bounds.y() + pos.y() * bounds.height();

//            vertices[i].set(x, y);
//        }
        QPointF p = position();
        vertices[0].x = p.x() - width()/2.f;
        vertices[0].y = p.y();
        vertices[1].x = p.x() + width()/2.f;
        vertices[1].y = p.y();
        return node;
    }
}
