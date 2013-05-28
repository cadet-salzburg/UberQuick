#include "Canvas.h"
#include <QSGGeometryNode>
#include "Items/Item.h"

namespace Uber {
    Canvas::Canvas(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Geometry( QSGGeometry::defaultAttributes_Point2D(), 4)
    {
        setFlag(ItemHasContents);
        setFiltersChildMouseEvents(true);
    }

    QColor Canvas::getColor() const
    {
        return m_Material.color();
    }

    void Canvas::setColor( const QColor &color)
    {
        m_Material.setColor(color);
    }

    bool Canvas::childMouseEventFilter(QQuickItem * item, QEvent * event)
    {
        Q_UNUSED(event);
        qDebug() << " The item is: " << item->metaObject()->className();
        QList<QQuickItem *> children  = childItems();
        qDebug() << "The number of children are: " << children.size();

        for ( int i = 0; i< children.size(); ++i )
        {
            qDebug() <<  "Child " << i << ": " << children.at(i)->metaObject()->className();
        }
        return false;



//        QPointF p = mapFromItem( item, QPointF( item->x(), item->y() ) );
//        QQuickItem* it = childAt( p.x(), p.y() );
//        if ( it )
//        {
//             qDebug() << it->metaObject()->className();
//             qDebug() << " ---------- ";
//             qDebug() << item->metaObject()->className();
//             qDebug() << "========" << item->parentItem()->metaObject()->className();
//        }
        //qDebug() << item->metaObject()->className();
        return true;
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
