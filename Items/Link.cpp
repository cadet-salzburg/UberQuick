#include "Link.h"

namespace Uber {
    Link::Link(QObject *parent)
    :Item(parent)
    ,m_Inlet(nullptr)
    ,m_Outlet(nullptr)
    {

    }

    Link::Link(Inlet *inlet, Outlet *outlet, QObject *parent )
    :Item(parent)
    ,m_Inlet(inlet)
    ,m_Outlet(outlet)
    {

    }

    Link::Link(const Link &other)
    :Item(other.parent())
    ,m_Inlet(other.getInlet())
    ,m_Outlet(other.getOutlet())
    {

    }

    Inlet *Link::getInlet() const
    {
        return m_Inlet;
    }

    Outlet *Link::getOutlet() const
    {
        return m_Outlet;
    }

    void Link::link()
    {
        m_Inlet->getInletHandle().link(m_Outlet->getOutletHandle());
    }

    void Link::unlink()
    {
        m_Inlet->getInletHandle().unlinkFrom(m_Outlet->getOutletHandle());
    }

    QSGNode* Link::updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData )
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
    void Link::updateLinkNodes()
    {
        qDebug() << "Link::updateLinkNodes() was called.";
    }
}
