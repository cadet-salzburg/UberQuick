#include "TextIO.h"
#include "InterfaceInlet.h"
#include "InterfaceOutlet.h"
namespace Uber {
    TextIO::TextIO()
    :InterfaceElement()
    ,m_Value("")
    {
        initialize();
    }

    TextIO::~TextIO()
    {
    }

    QVariant TextIO::getValue() const
    {
        return m_Value;
    }

    void TextIO::setValue(const QVariant &value)
    {
        if ( m_Value != value )
        {
            m_Value = value;
            emit valueChanged(value);
        }
    }

    void TextIO::initialize()
    {
        InterfaceInlet *currentInlet( new InterfaceInlet());
        appendInlet(currentInlet);

        InterfaceOutlet *currentOutlet( new InterfaceOutlet());
        appendOutlet(currentOutlet);

        QObject::connect(currentInlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setValue(QVariant)));
        QObject::connect(this, SIGNAL(valueChanged(QVariant)), currentOutlet, SLOT(setValue(QVariant)));
    }

}
