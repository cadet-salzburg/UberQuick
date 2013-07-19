#include "Image.h"
namespace Uber {
    Image::Image()
    :InterfaceElement()
    {

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

    void Image::setImage(const QVariant &img)
    {
        QImage img =img.value<QImage>();
        if ( m_Image != img )
        {
            m_Image = img;
            emit imageChanged(m_Image);
        }
    }

    void Image::initialize()
    {
        InterfaceInlet *currentOutlet( new InterfaceInlet());
        appendInlet(currentOutlet);
        QObject::connect(currentInlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
    }
}
