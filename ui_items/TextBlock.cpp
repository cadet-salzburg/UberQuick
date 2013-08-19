#include "TextBlock.h"
#include "InterfaceInlet.h"
#include "InterfaceOutlet.h"
namespace Uber {
    TextBlock::TextBlock()
    :InterfaceBlock()
    ,m_Value("")
    {
        initialize();
    }

    TextBlock::~TextBlock()
    {
    }

    QVariant TextBlock::getValue() const
    {
        return m_Value;
    }

    void TextBlock::setValue(const QVariant &value)
    {
        if ( m_Value != value )
        {
            m_Value = value;
            emit valueChanged(value);
        }
    }

    void TextBlock::initialize()
    {
        InterfaceInlet *currentInlet( new InterfaceInlet());
        appendInlet(currentInlet);

        InterfaceOutlet *currentOutlet( new InterfaceOutlet());
        appendOutlet(currentOutlet);

        QObject::connect(currentInlet, SIGNAL(valueChanged(QVariant)), this, SLOT(setValue(QVariant)));
        QObject::connect(this, SIGNAL(valueChanged(QVariant)), currentOutlet, SLOT(setValue(QVariant)));
        m_Classname = metaObject()->className();
    }

}
