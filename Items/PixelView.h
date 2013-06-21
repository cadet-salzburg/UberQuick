#ifndef PIXELVIEW_H
#define PIXELVIEW_H

#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QSGTexture>

namespace Uber {
    class PixelView : public QQuickItem
    {
        Q_OBJECT
    public:
        explicit PixelView(QQuickItem *parent = 0);
        virtual ~PixelView();
        QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *data);
    signals:

    public slots:
    private:
        QScopedPointer<QSGTexture> m_Texture;
    };
}
#endif // PIXELVIEW_H
