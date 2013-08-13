#ifndef BASEINLET_H
#define BASEINLET_H
#include <QVariant>
#include "Item.h"
namespace Uber {
    class BaseInlet : public Item
    {
        Q_OBJECT
    public:
        BaseInlet(QObject *parent = 0);
        BaseInlet(const BaseInlet &other);
        virtual ~BaseInlet();
        virtual inline bool isValid() const
        {
            return false;
        }

    signals:
        void            valueChanged(QVariant val);
    public slots:
        virtual void    setValue(QVariant val)
        {
            //
        }
    };
}
#endif // BASEINLET_H
