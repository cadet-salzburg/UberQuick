#include "Testrect.h"
#include <QSGGeometryNode>

namespace Uber {
    Testrect::Testrect(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Geometry( QSGGeometry::defaultAttributes_Point2D(), 4)
    {
        setFlag(ItemHasContents);
        setEnabled(true);
        setAcceptedMouseButtons(Qt::AllButtons);
    }

    QColor Testrect::getColor() const
    {
        return m_Material.color();
    }

    void Testrect::setColor( const QColor &color)
    {
        m_Material.setColor(color);
    }

    QSGNode *Testrect::updatePaintNode(QSGNode *n, UpdatePaintNodeData *d)
    {
        QSGGeometryNode *node = static_cast<QSGGeometryNode*>(n);
        if (!node) node = new QSGGeometryNode();
        QSGGeometry::Point2D *v = m_Geometry.vertexDataAsPoint2D();
        const QRectF rect = boundingRect();
        v[0].x = rect.left();
        v[0].y = rect.bottom();
        v[1].x = rect.right();
        v[1].y = rect.bottom();
        v[2].x = rect.left();
        v[2].y = rect.top();
        v[3].x = rect.right();
        v[3].y = rect.top();
        node->setGeometry(&m_Geometry);
        node->setMaterial(&m_Material);
        return node;
    }
}
