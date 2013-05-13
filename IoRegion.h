#ifndef IOREGION_H
#define IOREGION_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

namespace Uber {
    class IoRegion : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY( QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL )
        Q_PROPERTY( float radius READ getRadius WRITE setRadius NOTIFY radiusChanged FINAL )
    public:
        IoRegion(QQuickItem *parent = 0);

        QColor                  getColor() const;
        void                    setColor( const QColor &color);

        float                   getRadius() const;
        void                    setRadius( const float &radius );

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
#endif // IOREGION_H
