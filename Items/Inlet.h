#ifndef INLET_H
#define INLET_H

#include <QSharedPointer>
#include "Item.h"
#include "_2RealApplication.h"

using namespace _2Real::app;
namespace Uber {
    class Inlet : public Item
    {
        Q_OBJECT
    public:
        Inlet(QObject *parent = 0);
        Inlet(const Inlet &other);
        virtual ~Inlet();
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
            return m_Name;
        }

    private:
        QString         m_Name;
    signals:
    public slots:
    };
    typedef QSharedPointer<Inlet> InletRef;
    Q_DECLARE_METATYPE(Inlet)
}
#endif // INLET_H
