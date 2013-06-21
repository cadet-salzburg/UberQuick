#ifndef PIXELVIEW_H
#define PIXELVIEW_H

#include <QQuickItem>
#include <QSGFlatColorMaterial>
namespace Uber {
    class PixelView : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(int width READ getWidth WRITE setWidth NOTIFY widthChanged )
        Q_PROPERTY(int height READ getHeight WRITE setHeight NOTIFY heightChanged )
    public:
        explicit PixelView(QQuickItem *parent = 0);
        virtual ~PixelView();
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
        void        setHeight( int h );
        int         getHeight() const;
        void        setWidth( int w );
        void        getWidth() const;
    signals:
        void        widthChanged();
        void        heightChanged();
    public slots:
    private:
        int m_Height;
        int m_Width;
    };
}
#endif // PIXELVIEW_H
