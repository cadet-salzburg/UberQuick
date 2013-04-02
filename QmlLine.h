#ifndef QMLLIME_H
#define QMLLINE_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

namespace Uber {
    class QmlLine : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(float width READ getWidth WRITE setWidth NOTIFY widthChanged FINAL )
        Q_PROPERTY(float thickness READ getThickness WRITE setThickness NOTIFY thicknessChanged FINAL )
        Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL )
    public:
        explicit                QmlLine(QQuickItem *parent = 0);
        QSGNode*                updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData );

        void                    setWidth( float width );
        float                   getWidth() const;
        void                    setThickness( float thickness );
        float                   getThickness( ) const;
        void                    setColor( const QColor& color );
        QColor                  getColor() const;

    private:
        float                   m_Width;
        float                   m_Thickness;
        QColor                  m_Color;
        QSGGeometry             m_Geometry;
        QSGFlatColorMaterial    m_Material;
    signals:
        void                    widthChanged();
        void                    colorChanged();
        void                    thicknessChanged();
    public slots:
    };
}
#endif // QMLLINE_H
