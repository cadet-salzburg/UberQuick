#ifndef BLOCK_H
#define BLOCK_H

#include <QList>
#include <QSharedPointer>

#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"

namespace Uber {
    class Block : public Item
    {
        Q_OBJECT
    public:
        Block(QObject *parent = 0);
        Block( const Block &other);
        ~Block();

    signals:
    public slots:
    protected:
        //virtual  QString    getType() const;
    private:
        QList<InletRef>     m_Inlets;
        QList<OutletRef>    m_Outlets;
    };
    typedef QSharedPointer<Block> BlockRef;
    Q_DECLARE_METATYPE(Block)
}
#endif // BLOCK_H
