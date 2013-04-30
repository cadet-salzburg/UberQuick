#ifndef TESTRECT_H
#define TESTRECT_H

#include <QQuickItem>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>

namespace Uber {
    class Testrect : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL )
    public:
        Testrect(QQuickItem *parent = 0);
        QColor                  getColor() const;
        void                    setColor( const QColor &color);
    protected:
        QSGNode*                updatePaintNode( QSGNode *node, UpdatePaintNodeData *data);
    private:
        QSGGeometry             m_Geometry;
        QSGFlatColorMaterial    m_Material;
    signals:
        void colorChanged(const QColor &color);
    public slots:
    };
}
#endif // TESTRECT_H
