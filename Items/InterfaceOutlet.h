#ifndef INTERFACEOUTLET_H
#define INTERFACEOUTLET_H
#include "Outlet.h"
namespace Uber {
    class InterfaceOutlet : public Outlet
    {
        Q_OBJECT
    public:
        InterfaceOutlet();
        virtual ~InterfaceOutlet();
        virtual inline bool     isValid() const
        {
            return true;
        }

    private:
    signals:
    public slots:
    };
}
#endif // INTERFACEOUTLET_H
