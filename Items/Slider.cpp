#include "Slider.h"
#include <QDebug>
#include "InterfaceOutlet.h"
namespace Uber {
    Slider::Slider()
    :InterfaceElement()
    ,m_Multiplier(1.f)
    ,m_Offset(0.f)
    {
        initialize();
    }
    Slider::~Slider()
    {

    }
    void    Slider::initialize()
    {
        InterfaceOutlet *currentOutlet( new InterfaceOutlet());
        appendOutlet(currentOutlet);
    }

    void    Slider::setMultiplier( float m )
    {
        m_Multiplier = m;
    }
    float   Slider::getMultiplier() const
    {
        return m_Multiplier;
    }
    void    Slider::setOffset( float offset )
    {
        m_Offset = offset;
    }
    float   Slider::getOffset() const
    {
        return m_Offset;
    }
    QDebug operator << (QDebug dbg, const Slider &slider )
    {
        Q_UNUSED(slider)
        dbg.nospace() << "Slider";
        return dbg.maybeSpace();
    }
}
