#include <QSGGeometryNode>
#include "Canvas.h"
#include "Item.h"
#include "../system/System.h"
#include "../system/ConnectionManager.h"

namespace Uber {
Canvas::Canvas(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Geometry( QSGGeometry::defaultAttributes_Point2D(), 4)
{
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsDrops, true );
    setFiltersChildMouseEvents(false);
}

QColor Canvas::getColor() const
{
    return m_Material.color();
}

void Canvas::setColor( const QColor &color)
{
    m_Material.setColor(color);
}


void    Canvas::dragEnterEvent(QDragEnterEvent * event)
{
    event->accept();
}



void    Canvas::dragMoveEvent(QDragMoveEvent * event)
{
    System::getInstance()->getConnectionManager()->updateLink(event->pos() );
}

void    Canvas::dropEvent(QDropEvent * event)
{
    event->ignore();
    System::getInstance()->getConnectionManager()->removeLink();
}

QSGNode *Canvas::updatePaintNode(QSGNode *n, UpdatePaintNodeData *d)
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
