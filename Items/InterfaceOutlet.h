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
    public slots:
        void setValue(QVariant val)
        {
            if ( val != m_Value )
            {
                m_Value = val;
                emit valueChanged(m_Value);
            }
        }
    private:
        QVariant    m_Value;
    };
}
#endif // INTERFACEOUTLET_H
