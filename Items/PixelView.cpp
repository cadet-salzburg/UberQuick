#include "PixelView.h"
#include <QSGGeometryNode>
#include <QSGSimpleTextureNode>
#include <QPainter>
namespace Uber {
    PixelView::PixelView(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Data(nullptr)
    ,m_Texture(nullptr)
    {
        setFlag(ItemHasContents);
        setEnabled(true);
        m_Texture = new UberTexture();
    }

    PixelView::~PixelView()
    {
        delete m_Texture;
    }

    QSGNode* PixelView::updatePaintNode(QSGNode * node, QQuickItem::UpdatePaintNodeData *data)
    {
        if ( node || width() <= 0 || height() <= 0 )
        {
            delete node;
            node = nullptr;
        }
        node = new QSGSimpleTextureNode;
        static_cast<QSGSimpleTextureNode*>(node)->setFiltering(QSGTexture::Nearest);
        static_cast<QSGSimpleTextureNode*>(node)->setRect(boundingRect());
        QSGTexture* tex;
        if ( !m_Data )
        {
            tex = createTextureFromImage(m_Image);
        } else {
            std::shared_ptr< const _2Real::Image> outty = _2Real::Image::asImage( m_Data );
            m_Texture->setData(outty);
            tex = m_Texture;
        }
        assert(tex);
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
        m_Image = image;
        emit imageChanged(m_Image);
        update();
    }

    QImage PixelView::getImage() const
    {
        return m_Image;
    }

    void PixelView::setValue(const QVariant &image)
    {
        m_Data = image.value<std::shared_ptr<const _2Real::CustomType> >();
//        std::shared_ptr< const _2Real::Image> outty = _2Real::Image::asImage( m_Data );
//        m_Image = QImage( outty->getPixels(), outty->getWidth(), outty->getHeight(), QImage::Format_RGB888 );
//        emit valueChanged(m_Data);
        update();
    }

    QVariant PixelView::getValue() const
    {
        return QVariant::fromValue(m_Data);
    }
}
