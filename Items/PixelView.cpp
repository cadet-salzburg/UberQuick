#include "PixelView.h"
#include <QSGGeometryNode>
#include <QSGSimpleTextureNode>
#include <QPainter>
namespace Uber {
    PixelView::PixelView(QQuickItem *parent)
    :QQuickItem(parent)
    ,m_Path(":/images/default-img.png")
    ,m_Image(nullptr)
    ,m_PlaceholderImage(nullptr)
    ,m_Texture(nullptr)
    {
        setFlag(ItemHasContents);
        setEnabled(true);
        m_Texture = new UberTexture();
        initialize();
    }

    PixelView::~PixelView()
    {
        delete m_Texture;
    }

    QSGNode* PixelView::updatePaintNode(QSGNode * node, QQuickItem::UpdatePaintNodeData *data)
    {
        if ( node )
        {
            delete node;
            node = nullptr;
        }



        if ( width() <= 0 || height() <= 0 )
        {
            return nullptr;
        }
        node = new QSGSimpleTextureNode;
        static_cast<QSGSimpleTextureNode*>(node)->setFiltering(QSGTexture::Nearest);
        static_cast<QSGSimpleTextureNode*>(node)->setRect(boundingRect());
        QSGTexture* tex;
        if ( !m_Image )
        {
            m_Texture->setData(m_PlaceholderImage);
        } else {
            m_Texture->setData(m_Image);
        }
        tex = m_Texture;
        assert(tex);
        static_cast<QSGSimpleTextureNode*>(node)->setTexture(tex);
        return node;
    }

    void PixelView::setPlaceholderPath(const QString &path)
    {
        if ( m_Path != path )
        {
            m_Path = path;
            initialize();
            emit placeholderPathChanged(m_Path);
        }
    }

    QString PixelView::getPlaceholderPath() const
    {
        return m_Path;
    }

    void PixelView::setImage(QVariant image)
    {
        m_Image = image.value<ImageConstRef>();
        emit imageChanged(image);
        update();
    }

    QVariant PixelView::getImage() const
    {
        return QVariant::fromValue( m_Image );
    }

    void PixelView::initialize()
    {
        QImage img;
        img.load(m_Path);
        m_PlaceholderImage = ImageRef( new _2Real::Image());
        QImage::Format f = img.format();
        m_PlaceholderImage->setImagedata<uchar>(img.bits(),img.width(),img.height(), _2Real::Image::ChannelOrder::ARGB, _2Real::Image::Datatype::UINT8);
    }
}
