#ifndef PIXELVIEW_H
#define PIXELVIEW_H

#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QSGTexture>
#include <QImage>
#include "System.h"

namespace Uber {
    class PixelView : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY( QImage image READ getImage WRITE setImage NOTIFY imageChanged)
    public:
        explicit PixelView(QQuickItem *parent = 0);
        virtual ~PixelView();

        QSGNode*        updatePaintNode(QSGNode *node, UpdatePaintNodeData *data);
        QSGTexture*     createTextureFromImage(const QImage & image) const;

        void            setImage(const QImage& image );
        QImage          getImage() const;

    signals:
        void            imageChanged(QImage);

    public slots:
    private:
        QImage           m_Image;
        QImage           m_DefaultImage;
    };
}
#endif // PIXELVIEW_H
