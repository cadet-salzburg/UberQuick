#ifndef BLOCK_H
#define BLOCK_H
#include "Item.h"
#include "_2RealApplication.h"

namespace Uber {
    using namespace _2Real::app;
    class InletObjectListModel;
    class OutletObjectListModel;
    class Block : public Item
    {
        Q_OBJECT
        Q_PROPERTY( QString name READ getName WRITE setName NOTIFY nameChanged )
    public:
        Block();
        Block( const BlockHandle& handle, QString name= "" );
        Block( const Block &other);
        virtual ~Block();
        void                                        setName( QString name );
        Q_INVOKABLE QString                         getName();
        // It seems that the QT mocing has a bug and requires to use the namespace in the return type.
        // More here: http://stackoverflow.com/questions/14086289/use-c-slot-in-qml-which-returns-type-in-namespace
        Q_INVOKABLE Uber::InletObjectListModel*     getInletModel() const;
        Q_INVOKABLE Uber::OutletObjectListModel*    getOutletModel() const;

        Q_INVOKABLE int                             getNumberOfInlets();

        Q_INVOKABLE int                             getNumberOfOutlets();

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
    QDebug operator<<(QDebug dbg, const Block &block);
}
#endif // BLOCK_H
