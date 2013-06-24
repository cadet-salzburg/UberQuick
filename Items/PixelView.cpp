#include "PixelView.h"
#include <QSGGeometryNode>
#include <QSGSimpleTextureNode>
namespace Uber {
//    PixelView::PixelView(QQuickItem *parent)
//    :QQuickItem(parent)
//    {

//    }

//    PixelView::~PixelView()
//    {

//    }

//    QSGNode *PixelView::updatePaintNode(QSGNode * node, QQuickItem::UpdatePaintNodeData *data)
//    {
//        if (width() <= 0 || height() <= 0)
//        {
//          m_Texture->reset();
//          delete node;
//          node = 0;
//        }  else {
//            if (!node)
//            {
//                node = new QSGSimpleTextureNode;
//                static_cast<QSGSimpleTextureNode*>(node)->setFiltering(QSGTexture::Nearest);
//            }
//            static_cast<QSGSimpleTextureNode*>(node)->setRect(boundingRect());
//            //Get the texture... maybe here we need to lock here or something
//            Q_ASSERT(m_Texture);
//            static_cast<QSGSimpleTextureNode*>(node)->setTexture(m_Texture.data());
//        }
//        return node;
//    }
}
