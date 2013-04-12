#ifndef BLOCK_H
#define BLOCK_H
#include <QList>
#include <QSharedPointer>
#include "_2RealApplication.h"
#include "Item.h"
#include "Inlet.h"
#include "Outlet.h"
#include "../Models/InletObjectListModel.h"
#include "../Models/OutletObjectListModel.h"

using namespace _2Real::app;
namespace Uber {
    class Block : public Item
    {
        Q_OBJECT
        Q_PROPERTY( QString name READ getName WRITE setName NOTIFY nameChanged )
    public:
        Block();
        Block( const BlockHandle& handle );
        Block( const Block &other);
        ~Block();
        void                                        setName( QString name );
        Q_INVOKABLE QString                         getName();
        // It seems that the QT mocing has a bug and requires to use the namespace in the return type.
        // More here: http://stackoverflow.com/questions/14086289/use-c-slot-in-qml-which-returns-type-in-namespace
        Q_INVOKABLE Uber::InletObjectListModel*     getInletModel() const;
        Q_INVOKABLE Uber::OutletObjectListModel*    getOutletModel() const;

        Q_INVOKABLE int                             getNumberOfInlets()
        {
            return m_InletModel->count();
        }

        Q_INVOKABLE int                             getNumberOfOutlets()
        {
            return m_OutletModel->count();
        }

        void                                        setBlockHandle( const BlockHandle& handle );
        BlockHandle                                 getBlockHandle() const;
    signals:
        void                                        nameChanged();
    public slots:
    protected:
    private:
        QString                                     m_Name;
        BlockHandle                                 m_BlockHandle;
        InletObjectListModel*                       m_InletModel;
        OutletObjectListModel*                      m_OutletModel;
        void                                        initialize();
    };
    typedef QSharedPointer<Block> BlockRef;
    QDebug operator<<(QDebug dbg, const Block &block);
    //Q_DECLARE_METATYPE(Block)
}

#endif // BLOCK_H
