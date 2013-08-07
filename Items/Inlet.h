#ifndef INLET_H
#define INLET_H
#include <QVariant>
#include "Item.h"
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
        QString     m_Name;
    signals:
        void valueChanged(QVariant val);
    public slots:
        virtual void setValue(QVariant val)
        {
            //
        }
    };
}
#endif // INLET_H
