#include "Image.h"
#include "InterfaceInlet.h"
#include "../system/System.h"
#include "InletObjectListModel.h"
#include "OutletObjectListModel.h"

namespace Uber {
    Image::Image()
    :InterfaceBlock()
    ,m_Image(nullptr)
    {
        cnt = 0;
        initialize();
    }

    Image::~Image()
    {
        qDebug() << "Image Destructor";
        disconnectSignals();
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

    void Image::connectSignals()
    {
        InletObjectListModel *model = getInletModel();
        BaseInlet* inlet = model->at(0);
        QObject::connect(inlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
    }

    void Image::disconnectSignals()
    {
        InletObjectListModel *model = getInletModel();
        BaseInlet* inlet = model->at(0);
        QObject::disconnect(inlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
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
        connectSignals();
    }
}
