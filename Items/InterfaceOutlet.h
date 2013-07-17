#ifndef INTERFACEOUTLET_H
#define INTERFACEOUTLET_H
#include <QDebug>
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
    public slots:
        void setValue(QVariant val)
        {
            if ( val != m_Value )
            {
                m_Value = val;
                emit valueChanged(m_Value);
            }
            qDebug() << " Interface Outlet Value: " << val;
        }
    private:
        QVariant    m_Value;
    };
}
#endif // INTERFACEOUTLET_H
