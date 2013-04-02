#ifndef BLOCK_H
#define BLOCK_H
#include <QList>
#include <QSharedPointer>
#include "_2RealApplication.h"
#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"
using namespace _2Real::app;
namespace Uber {
    class Block : public Item
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ getName WRITE setName)
    public:
        Block();
        Block( const BlockHandle& handle );
        Block( const Block &other);
        ~Block();
        void                            setName( QString name );
        QString                         getName();
        Q_INVOKABLE QList<InletRef>     getInlets() const;
        Q_INVOKABLE QList<OutletRef>    getOutlets() const;

        void                            setBlockHandle( const BlockHandle& handle );
        BlockHandle                     getBlockHandle() const;
    signals:

    public slots:
    protected:
        //virtual  QString    getType() const;
    private:
        QList<InletRef>                 m_Inlets;
        QList<OutletRef>                m_Outlets;
        QString                         m_Name;
        BlockHandle                     m_BlockHandle;
        void                            initialize();
    };
    typedef QSharedPointer<Block> BlockRef;
    QDebug operator<<(QDebug dbg, const Block &block);
    Q_DECLARE_METATYPE(Block)
}
#endif // BLOCK_H
