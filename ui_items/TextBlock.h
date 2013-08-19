#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H
#include "InterfaceBlock.h"
#include <QVariant>
namespace Uber {
    class TextBlock : public InterfaceBlock
    {
        Q_OBJECT
        Q_PROPERTY( QVariant value READ getValue WRITE setValue NOTIFY valueChanged )
    public:
        TextBlock();
        virtual ~TextBlock();
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
#endif // TEXTBLOCK_H
