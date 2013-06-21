#include "PixelView.h"

namespace Uber {
    PixelView::PixelView(QQuickItem *parent)
    :QQuickItem(parent)
    {

    }

    PixelView::~PixelView()
    {
    }

    QSGNode *PixelView::updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *)
    {

    }

    void PixelView::setHeight(int h)
    {
        m_Height = h;
    }

    int PixelView::getHeight() const
    {
        return m_Height;
    }

    void PixelView::setWidth(int w)
    {
        m_Width = w;
    }

    void PixelView::getWidth() const
    {
        return m_Width;
    }
}
