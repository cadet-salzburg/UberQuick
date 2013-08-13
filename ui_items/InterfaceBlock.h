#ifndef INTERFACEBLOCK_H
#define INTERFACEBLOCK_H
#include "BaseBlock.h"

namespace Uber {
    class BaseInlet;
    class BaseOutlet;
    class InterfaceBlock : public BaseBlock
    {
        Q_OBJECT
    public:
        InterfaceBlock();
        virtual ~InterfaceBlock();

        void    appendInlet(BaseInlet *inlet);
        void    appendOutlet(BaseOutlet *outlet);
    };
}
#endif // INTERFACEELEMENT_H
