#ifndef IMAGE_H
#define IMAGE_H
#include "InterfaceElement.h"
#include <QImage>
#include "../system/System.h"
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"
#include <memory>

namespace Uber {
#ifndef IMAGE_TYPEDEFS
#define IMAGE_TYPEDEFS
    typedef std::shared_ptr<const _2Real::Image> ImageConstRef;
    typedef std::shared_ptr<_2Real::Image> ImageRef;
#endif
}

namespace Uber {
    class Image : public InterfaceElement
    {
        Q_OBJECT
        Q_PROPERTY( int minWidth READ getMinWidth WRITE setMinWidth NOTIFY minWidthChanged )
        Q_PROPERTY( int maxWidth READ getMaxWidth WRITE setMaxWidth NOTIFY maxWidthChanged )
        Q_PROPERTY( qreal aspectRatio READ getAspectRatio NOTIFY aspectRatioChanged )
        Q_PROPERTY( QVariant image READ getImage WRITE setImage NOTIFY imageChanged )
    public:
        Image();
        qreal           getAspectRatio() const;
        void            setMinWidth( int w );
        int             getMinWidth() const;
        void            setMaxWidth( int w );
        int             getMaxWidth() const;
        QVariant        getImage() const;
    signals:
        void            minWidthChanged(int);
        void            maxWidthChanged(int);
        void            imageChanged(QVariant);
        void            aspectRatioChanged(qreal);

        void            valueChanged();
    public slots:
        void            setImage(QVariant img);
    private:
        qreal           m_AspectRatio;
        int             m_MinWidth;
        int             m_MaxWidth;
        ImageConstRef   m_Image, m_ImageKeep;
        virtual void    initialize();
        int             cnt;
    };
}
#endif // IMAGE_H
