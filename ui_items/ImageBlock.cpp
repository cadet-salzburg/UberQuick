#include "ImageBlock.h"
#include "InterfaceInlet.h"
#include "../system/System.h"
#include "InletObjectListModel.h"
#include "OutletObjectListModel.h"

namespace Uber {
    ImageBlock::ImageBlock()
    :InterfaceBlock()
    ,m_Image(nullptr)
    {
                qDebug() << " constructor image called";
        cnt = 0;
        initialize();
    }

    ImageBlock::~ImageBlock()
    {
        qDebug() << "Image Destructor";
        disconnectSignals();
    }

    qreal ImageBlock::getAspectRatio() const
    {
        return m_Image->getWidth()/m_Image->getHeight();
    }

    void ImageBlock::setMinWidth(int w)
    {
        if ( m_MinWidth != w )
        {
            m_MinWidth = w;
            emit minWidthChanged(m_MinWidth);
        }
    }

    int ImageBlock::getMinWidth() const
    {
        return m_MinWidth;
    }

    void ImageBlock::setMaxWidth(int w)
    {
        if ( m_MaxWidth != w )
        {
            m_MaxWidth = w;
            emit maxWidthChanged(m_MaxWidth);
        }
    }

    int ImageBlock::getMaxWidth() const
    {
        return m_MaxWidth;
    }

    QVariant ImageBlock::getImage() const
    {
        return QVariant::fromValue( m_Image );
    }

    void ImageBlock::connectSignals()
    {
        InletObjectListModel *model = getInletModel();
        BaseInlet* inlet = model->at(0);
        QObject::connect(inlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
    }

    void ImageBlock::disconnectSignals()
    {
        InletObjectListModel *model = getInletModel();
        BaseInlet* inlet = model->at(0);
        QObject::disconnect(inlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setImage(QVariant)));
    }

    void ImageBlock::setImage(QVariant img)
    {
        m_Image = img.value<ImageConstRef>();
        emit imageChanged(img);
    }

    void ImageBlock::initialize()
    {
        InterfaceInlet *currentInlet( new InterfaceInlet());
        appendInlet(currentInlet);
        connectSignals();
        m_Classname = metaObject()->className();
    }
}
