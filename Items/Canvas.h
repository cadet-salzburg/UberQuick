#ifndef CANVAS_H
#define CANVAS_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>


namespace Uber {
    class Canvas : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL )
    public:
        Canvas(QQuickItem *parent = 0);
        QColor                  getColor() const;
        void                    setColor( const QColor &color);
    protected:

        virtual void            dragEnterEvent(QDragEnterEvent * event);
        virtual void            dragMoveEvent(QDragMoveEvent * event);
        virtual void            dropEvent(QDropEvent * event);

        QSGNode*                updatePaintNode( QSGNode *node, UpdatePaintNodeData *data);
    private:
        QSGGeometry             m_Geometry;
        QSGFlatColorMaterial    m_Material;
    signals:
        void                    colorChanged(const QColor &color);
    public slots:
    };
}
#endif // CANVAS_H
