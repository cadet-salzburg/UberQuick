#ifndef LINK_H
#define LINK_H
#include <QQuickItem.h>
#include "Inlet.h"
#include "Outlet.h"

namespace Uber {
    class Link : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QPointF startPosition READ getStart WRITE setStart NOTIFY startPositionChanged )
        Q_PROPERTY(QPointF endPosition READ getEnd WRITE setEnd NOTIFY endPositionChanged )
    public:
        enum DisplayOption {
            SingleLine,
            MultiLine
        };

        Link( QObject *parent = nullptr );
        Link( Inlet *inlet, Outlet *outlet, QObject *parent = nullptr );
        Link( const Link &other );

        QSGNode*            updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData );

        Inlet*              getInlet() const;
        Outlet*             getOutlet() const;

        void                link();
        void                unlink();

        QPointF             getStart() const;
        void                setStart( QPointF start );

        QPointF             getEnd() const;
        void                setEnd( QPointF end );

        Q_INVOKABLE         setDisplayOption( DisplayOption option );

    private:
        Inlet*              m_Inlet;
        Outlet*             m_Outlet;
        QList<QPointF>      m_LinkNodes;
        DisplayOption       m_DisplayOption;
    signals:
        void                startPositionChanged( QPointF p );
        void                endPositionChanged( QPointF p );
    public slots:
        void                updateLinkNodes();
    };
}
#endif // LINK_H
