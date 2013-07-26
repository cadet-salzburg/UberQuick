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
    class PixelView : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY( QVariant value READ getValue WRITE setValue NOTIFY valueChanged)
        Q_PROPERTY( QImage image READ getImage WRITE setImage NOTIFY imageChanged)
    public:
        explicit PixelView(QQuickItem *parent = 0);
        virtual ~PixelView();

        QSGNode*        updatePaintNode(QSGNode *node, UpdatePaintNodeData *data);
        QSGTexture*     createTextureFromImage(const QImage & image) const;

        void            setImage(const QImage& image );
        void            setValue(const QVariant& image );

        QImage          getImage() const;
        QVariant        getValue() const;

    signals:
        void            imageChanged(QImage);
        void            valueChanged(QVariant);
    public slots:


    private:
        QImage           m_Image;
        QString          m_Path;
        std::shared_ptr<const _2Real::CustomType> m_Data;
        UberTexture     *m_Texture;
    };
}
#endif // PIXELVIEW_H
