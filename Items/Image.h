#ifndef IMAGE_H
#define IMAGE_H
#include "InterfaceElement.h"
namespace Uber {
    class Image : public InterfaceElement
    {
        Q_OBJECT
        Q_PROPERTY( int minWidth READ getMinWidth WRITE setMinWidth NOTIFY minWidthChanged )
        Q_PROPERTY( int maxWidth READ getMaxWidth WRITE setMaxWidth NOTIFY maxWidthChanged )
        Q_PROPERTY( qreal aspectRatio READ getAspectRatio NOTIFY aspectRatioChanged )
        Q_PROPERTY( QImage image READ getImage WRITE setImage NOTIFY imageChanged )
    public:
        Image();
        qreal   getAspectRatio() const;
        void    setMinWidth( int w );
        int     getMinWidth() const;
        void    setMaxWidth( int w );
        int     getMaxWidth() const;
    signals:
        void    valueChanged(QVariant newValue);
        void    minWidthChanged(int);
        void    maxWidthChanged(int);
        void    imageChanged(QImage);
        void    aspectRatioChanged(qreal);
    public slots:
        void    setImage(const QVariant& img );
    private:
        qreal   m_AspectRatio;
        int     m_MinWidth;
        int     m_MaxWidth;
        QImage  m_Image;
        void    initialize();
    };
}
#endif // IMAGE_H
