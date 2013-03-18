#ifndef INLET_H
#define INLET_H

#include <QSharedPointer>
#include "Item.h"

namespace Uber {

    class Inlet : public Item
    {
        Q_OBJECT
    public:
        Inlet(QObject *parent = 0);
        Inlet(const Inlet &other);
        ~Inlet();
    signals:
    public slots:
    };
    typedef QSharedPointer<Inlet> InletRef;
    Q_DECLARE_METATYPE(Inlet)
}
#endif // INLET_H
