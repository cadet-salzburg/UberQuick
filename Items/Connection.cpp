#include "Connection.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

namespace Uber {
    Connection::Connection(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_p1(0,0)
    ,m_p2(1,0)
    ,m_p3(0,1)
    ,m_p4(1,1)
    ,m_segmentCount(32)
    {
        setFlag( ItemHasContents, true );
    }

    Connection::~Connection()
    {

    }

    void Connection::setP1(const QPointF &p)
    {
        if ( p == m_p1 )
            return;
        m_p1 = p;
        emit p1Changed(p);
        update();
    }

    void Connection::setP2(const QPointF &p)
    {
        if ( p == m_p2 )
            return;
        m_p2 = p;
        emit p2Changed(p);
        update();
    }

    void Connection::setP3(const QPointF &p)
    {
        if ( p == m_p3 )
            return;
        m_p3 = p;
        emit p3Changed(p);
        update();
    }

    void Connection::setP4(const QPointF &p)
    {
        if ( p == m_p4 )
            return;
        m_p4 = p;
        emit p4Changed(p);
        update();
    }

    QSGNode *Connection::updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *)
    {
        QSGGeometryNode *node = 0;
        QSGGeometry *geometry = 0;
        if ( !oldNode )
        {
            node = new QSGGeometryNode ;
            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_segmentCount);
            geometry->setLineWidth(2);
            geometry->setDrawingMode(GL_LINE_STRIP);
            node->setGeometry(geometry);
            node->setFlag(QSGNode::OwnsGeometry);
            QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
            material->setColor(QColor(255, 0, 0));
            node->setMaterial(material);
            node->setFlag(QSGNode::OwnsMaterial);
        } else {
            node = static_cast<QSGGeometryNode *>(oldNode);
            geometry = node->geometry();
            geometry->allocate(m_segmentCount);
        }
        return node;
    }

    void Connection::setSegmentCount(int count)
    {
        if ( ( count == m_segmentCount )|| ( count <= 12 ) )
            return;
        m_segmentCount = count;
        emit segmentCountChanged(count);
        update();
    }
}
