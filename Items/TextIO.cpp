#include "TextIO.h"
#include "InterfaceInlet.h"
#include "InterfaceOutlet.h"
namespace Uber {
    TextIO::TextIO()
    :InterfaceElement()
    ,m_Text("")
    {
        initialize();
    }

    TextIO::~TextIO()
    {
    }

    void TextIO::setText(const QString &text)
    {
        m_Text = text;
    }

    QString TextIO::getText() const
    {
        return m_Text;
    }

    void TextIO::initialize()
    {
        InterfaceInlet *currentInlet( new InterfaceInlet());
        appendInlet(currentInlet);
        InterfaceOutlet *currentOutlet( new InterfaceOutlet());
        appendOutlet(currentOutlet);
    }

}
