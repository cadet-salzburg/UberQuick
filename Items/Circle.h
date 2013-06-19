#ifndef CIRCLE_H
#define CIRCLE_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

namespace Uber {
    class Circle : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY( QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL )
        Q_PROPERTY( float radius READ getRadius WRITE setRadius NOTIFY radiusChanged FINAL )
    public:
        Circle(QQuickItem *parent = 0);

        QColor                  getColor() const;
        void                    setColor( const QColor &color);

        float                   getRadius() const;
        void                    setRadius( const float &radius );

        Q_INVOKABLE QPointF     getSceneCoords( QQuickItem *item, const QPointF &p )
        {
            return mapToItem(item,p);
        }

    protected:
        QSGNode*                updatePaintNode( QSGNode *node, UpdatePaintNodeData *data);
    private:
        QSGGeometry             m_Geometry;
        QSGFlatColorMaterial    m_Material;
        float                   m_Radius;
    signals:
        void colorChanged(const QColor &color );
        void radiusChanged(const float &radius );
    public slots:
    };
}
#endif // CIRCLE_H
