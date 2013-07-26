#ifndef PIXELVIEW_H
#define PIXELVIEW_H

#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QSGTexture>
#include <QImage>
#include "System.h"
#include "UberTexture.h"
#include <memory>
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"

namespace Uber {
#ifndef IMAGE_TYPEDEFS
#define IMAGE_TYPEDEFS
    typedef std::shared_ptr<const _2Real::Image> ImageConstRef;
    typedef std::shared_ptr<_2Real::Image> ImageRef;
#endif
    class PixelView : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY( QVariant image READ getImage WRITE setImage NOTIFY imageChanged )
        Q_PROPERTY( QString placeholder READ getPlaceholderPath WRITE setPlaceholderPath NOTIFY placeholderPathChanged )
    public:
        explicit PixelView(QQuickItem *parent = 0);
        virtual ~PixelView();

        QSGNode*        updatePaintNode(QSGNode *node, UpdatePaintNodeData *data);

        void            setPlaceholderPath( const QString& path );
        QString         getPlaceholderPath() const;

        void            setImage( QVariant image );
        QVariant        getImage() const;

    signals:
        void            imageChanged(QVariant);
        void            placeholderPathChanged(QString);
    public slots:
    private:
        void            initialize();


    private:
        QString          m_Path;
        ImageConstRef    m_Image;
        ImageRef         m_PlaceholderImage;
        UberTexture     *m_Texture;
    };
}
#endif // PIXELVIEW_H
