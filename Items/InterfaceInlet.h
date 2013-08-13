#ifndef INTERFACEINLET_H
#define INTERFACEINLET_H
#include "BaseInlet.h"
#include <QVariant>
namespace Uber {
    class InterfaceInlet : public BaseInlet
    {
        Q_OBJECT
    public:
        InterfaceInlet( QObject *parent = 0 );
        virtual         ~InterfaceInlet();
        inline bool     isValid() const
        {
            return true;
        }
    public slots:
        void            setValue(QVariant val)
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
#endif // INTERFACEINLET_H
