#ifndef IMAGE_H
#define IMAGE_H
#include "InterfaceElement.h"
#include <QImage>
#include "../system/System.h"
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"
#include <memory>
namespace Uber {
    class Image : public InterfaceElement
    {
        Q_OBJECT
        Q_PROPERTY( int minWidth READ getMinWidth WRITE setMinWidth NOTIFY minWidthChanged )
        Q_PROPERTY( int maxWidth READ getMaxWidth WRITE setMaxWidth NOTIFY maxWidthChanged )
        Q_PROPERTY( qreal aspectRatio READ getAspectRatio NOTIFY aspectRatioChanged )
        Q_PROPERTY( QImage image READ getImage WRITE setImage NOTIFY imageChanged )
        Q_PROPERTY( QVariant value READ getValue WRITE setValue NOTIFY valueChanged )
    public:
        Image();
        qreal   getAspectRatio() const;
        void    setMinWidth( int w );
        int     getMinWidth() const;
        void    setMaxWidth( int w );
        int     getMaxWidth() const;
        QImage  getImage() const;
    signals:
        void    minWidthChanged(int);
        void    maxWidthChanged(int);
        void    imageChanged(QVariant);
        void    valueChanged(QVariant);
        void    aspectRatioChanged(qreal);
    public slots:
        void    setImage(const QImage& img );
        void    setImage(const QVariant& img);
        void    setValue(const QVariant& value);
    private:
        qreal   m_AspectRatio;
        int     m_MinWidth;
        int     m_MaxWidth;
        QImage  m_Image;
        std::shared_ptr<const _2Real::CustomType> m_Data;
        virtual void    initialize();
    };
}
#endif // IMAGE_H
