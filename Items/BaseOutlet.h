#ifndef BASEOUTLET_H
#define BASEOUTLET_H

#include <QVariant>
#include "Item.h"

namespace Uber {
    class BaseOutlet : public Item
    {
        Q_OBJECT
    public:
        BaseOutlet(QObject *parent = 0);
        BaseOutlet(const BaseOutlet &other);
        virtual ~BaseOutlet();

        virtual inline bool isValid() const
        {
            return false;
        }

    private:
    signals:
        void valueChanged(QVariant val);
    public slots:
    };
}
#endif // BASEOUTLET_H
