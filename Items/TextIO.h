#ifndef TEXTIO_H
#define TEXTIO_H
#include "InterfaceElement.h"

namespace Uber {
    class TextIO : public InterfaceElement
    {
        Q_OBJECT
        Q_PROPERTY( QString text READ getText WRITE setText NOTIFY textChanged )
    public:
        TextIO();
        virtual ~TextIO();
        void        setText( const QString &text);
        QString     getText() const;
    signals:
        void textChanged();
    private:
        QString m_Text;
        virtual void    initialize();
    };
}
#endif // TEXTIO_H
