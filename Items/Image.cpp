#include "Image.h"
#include "InterfaceInlet.h"


namespace Uber {
    Image::Image()
    :InterfaceElement()
    ,m_Image(nullptr)
    {
        cnt = 0;
        initialize();
    }

    qreal Image::getAspectRatio() const
    {
        return m_Image->getWidth()/m_Image->getHeight();
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

    QVariant Image::getImage() const
    {
        return QVariant::fromValue( m_Image );
    }

    void Image::setImage(QVariant img)
    {
        m_Image = img.value<ImageConstRef>();
        emit imageChanged(img);
    }
    void Image::initialize()
    {
        InterfaceInlet *currentInlet( new InterfaceInlet());
        appendInlet(currentInlet);
        QObject::connect(currentInlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
    }
}
