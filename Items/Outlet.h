#ifndef OUTLET_H
#define OUTLET_H

#include <QSharedPointer>
#include <QVariant>
#include "Item.h"
#include "_2RealApplication.h"

using namespace _2Real::app;
namespace Uber {
    class Outlet : public Item
    {
        Q_OBJECT
    public:
        Outlet(QObject *parent = 0);
        Outlet(const Outlet &other);
        virtual ~Outlet();

        virtual inline bool isValid() const
        {
            return false;
        }

        void setName( QString name )
        {
            m_Name = name;
        }
        Q_INVOKABLE QString getName()
        {
            return "Outlet";
        }
    private:
        QString m_Name;
    signals:
        void valueChanged(QVariant val);
        void killSelf();
    public slots:
    };
    typedef QSharedPointer<Outlet> OutletRef;
    Q_DECLARE_METATYPE(Outlet)
}
#endif // OUTLET_H
