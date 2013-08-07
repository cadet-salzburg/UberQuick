#ifndef TEXTIO_H
#define TEXTIO_H
#include "InterfaceElement.h"
#include <QVariant>
namespace Uber {
    class TextIO : public InterfaceElement
    {
        Q_OBJECT
        Q_PROPERTY( QVariant value READ getValue WRITE setValue NOTIFY valueChanged )
    public:
        TextIO();
        virtual ~TextIO();
        QVariant        getValue() const;
    signals:
        void            valueChanged(QVariant);
    public slots:
        void            setValue(const QVariant &value);
    private:
        QVariant        m_Value;
        virtual void    initialize();
    };
}
#endif // TEXTIO_H
