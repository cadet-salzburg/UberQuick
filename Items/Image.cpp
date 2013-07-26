#include "Image.h"
#include "InterfaceInlet.h"


namespace Uber {
    Image::Image()
    :InterfaceElement()
    ,m_Image(":/images/default-img.png")
    {
        initialize();
    }

    qreal Image::getAspectRatio() const
    {
        return m_Image.width()/m_Image.height();
    }

    void Image::setMinWidth(int w)
    {
        if ( m_MinWidth != w )
        {
            m_MinWidth = w;
            emit minWidthChanged(m_MinWidth);
        }
    }

    int Image::getMinWidth() const
    {
        return m_MinWidth;
    }

    void Image::setMaxWidth(int w)
    {
        if ( m_MaxWidth != w )
        {
            m_MaxWidth = w;
            emit maxWidthChanged(m_MaxWidth);
        }
    }

    int Image::getMaxWidth() const
    {
        return m_MaxWidth;
    }

    QImage Image::getImage() const
    {
        return m_Image;
    }

    void Image::setImage(const QImage &img)
    {
        m_Image = img;
    }

    void Image::setImage(const QVariant &img)
    {
        m_Data = img.value<std::shared_ptr<const _2Real::CustomType> >();
        std::shared_ptr< const _2Real::Image> outty = _2Real::Image::asImage( m_Data );
        m_Image = QImage( outty->getPixels(), outty->getWidth(), outty->getHeight(), QImage::Format_RGB888 );
        emit imageChanged(img);
    }

    void Image::initialize()
    {
        InterfaceInlet *currentInlet( new InterfaceInlet());
        appendInlet(currentInlet);
        QObject::connect(currentInlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
    }
}
