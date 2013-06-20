#ifndef INTERFACEINLET_H
#define INTERFACEINLET_H

namespace Uber {
    class InterfaceInlet : public Inlet
    {
        Q_OBJECT
    public:
        InterfaceInlet(QObject *parent = 0);
        InterfaceInlet(const InterfaceInlet &other);
        InterfaceInlet( const InletHandle &handle, QObject *parent = 0 );
        virtual ~InterfaceInlet();

        void            setInletHandle(const InletHandle& handle );
        InletHandle     getInletHandle() const;
        virtual inline bool     isValid() const
        {
            return m_InletHandle.isValid();
        }

    private:
        InletHandle     m_InletHandle;
    signals:
    public slots:
    };
}
#endif // INTERFACEINLET_H
