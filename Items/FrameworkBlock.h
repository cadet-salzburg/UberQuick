#ifndef BLOCK_H
#define BLOCK_H
#include "BaseBlock.h"
#include "_2RealApplication.h"

namespace Uber {
    using namespace _2Real::app;
    class FrameworkBlock : public BaseBlock
    {
        Q_OBJECT
    public:
        FrameworkBlock();
        FrameworkBlock( const BlockHandle& handle, QString name= "" );
        virtual         ~FrameworkBlock();
        void            setBlockHandle( const BlockHandle& handle );
        BlockHandle     getBlockHandle() const;
    protected:
        void            initialize();
    private:
        BlockHandle     m_BlockHandle;
    };
}
#endif // BLOCK_H
