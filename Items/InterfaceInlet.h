#ifndef INTERFACEINLET_H
#define INTERFACEINLET_H
#include "Inlet.h"
namespace Uber {
    class InterfaceInlet : public Inlet
    {
        Q_OBJECT
    public:
        InterfaceInlet(QObject *parent = 0);
        virtual ~InterfaceInlet();

        virtual inline bool     isValid() const
        {
            return true;
        }
    signals:

    public slots:
    };
}
#endif // INTERFACEINLET_H
