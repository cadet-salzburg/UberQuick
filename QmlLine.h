#ifndef QMLLIME_H
#define QMLLINE_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

namespace Uber {
    class QmlLine : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(float thickness READ getThickness WRITE setThickness NOTIFY thicknessChanged FINAL )
        Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL )
    public:
        explicit                QmlLine(QQuickItem *parent = 0);
        QSGNode*                updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData );

        void                    setThickness( float thickness );
        float                   getThickness( ) const;
        void                    setColor( const QColor& color );
        QColor                  getColor() const;

    private:
        float                   m_Thickness;
        QColor                  m_Color;
        QSGGeometry             m_Geometry;
        QSGFlatColorMaterial    m_Material;
        int                     m_SegmentCount;
    signals:
        void                    widthChanged();
        void                    colorChanged();
        void                    thicknessChanged();
    public slots:
    };
}
#endif // QMLLINE_H
