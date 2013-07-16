#ifndef INTERFACEINLET_H
#define INTERFACEINLET_H
#include "Inlet.h"
#include <QVariant>
#include <QDebug>
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
        void valueChanged(QVariant val);
    public slots:
        void setValue(QVariant val)
        {
            if ( val != m_Value )
            {
                m_Value = val;
                emit valueChanged(m_Value);
            }
            qDebug() << " Interface Inlet Value: " << val;
        }
    private:
        QVariant    m_Value;

    };
}
#endif // INTERFACEINLET_H
