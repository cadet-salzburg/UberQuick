#include "PixelView.h"
#include <QSGGeometryNode>
#include <QSGSimpleTextureNode>
#include <QPainter>
namespace Uber {
    PixelView::PixelView(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_DefaultImage(":/images/default-img.png")
    //,m_Image(m_DefaultImage)
    {
        setFlag(ItemHasContents);
        setEnabled(true);
//        QImage m_DefaultImage(":/images/default-img.png");
        setImage( m_DefaultImage );
        qDebug() << "constructor";
    }

    PixelView::~PixelView()
    {

    }

    QSGNode* PixelView::updatePaintNode(QSGNode * node, QQuickItem::UpdatePaintNodeData *data)
    {
        if ( node || width() <= 0 || height() <= 0 )
        {
            qDebug() << "WWW";
            delete node;
            node = nullptr;
            //return node;
        }
                    qDebug() << "WWAAAA";
        node = new QSGSimpleTextureNode;
        static_cast<QSGSimpleTextureNode*>(node)->setFiltering(QSGTexture::Nearest);
        static_cast<QSGSimpleTextureNode*>(node)->setRect(boundingRect());
        QSGTexture* tex = createTextureFromImage(m_Image);
        Q_ASSERT(tex);
        static_cast<QSGSimpleTextureNode*>(node)->setTexture(tex);
        return node;
    }

    QSGTexture* PixelView::createTextureFromImage(const QImage &image) const
    {
        QSGTexture *t = nullptr;
        if (!image.isNull())
        {
            t = System::getInstance()->getWindow()->createTextureFromImage(image);
        }
        return t;
    }

    void PixelView::setImage(const QImage &image)
    {
        if ( image != m_Image )
        {
            m_Image = image;
            emit imageChanged(m_Image);
        }
    }

    QImage PixelView::getImage() const
    {
        return m_Image;
    }
}
