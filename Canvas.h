#ifndef CANVAS_H
#define CANVAS_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

namespace Uber {
    class Canvas : public QQuickItem
    {
        Q_OBJECT
    public:
        Canvas(QQuickItem *parent = 0);
    protected:
        bool        childMouseEventFilter(QQuickItem * item, QEvent * event);
        QSGNode*    updatePaintNode( QSGNode *node, UpdatePaintNodeData *data);
    private:
        QSGGeometry m_Geometry;
        QSGFlatColorMaterial m_Material;
    signals:
    public slots:
    };
}
#endif // CANVAS_H
