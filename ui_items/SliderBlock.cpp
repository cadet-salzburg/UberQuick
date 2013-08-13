#include "SliderBlock.h"
#include <QDebug>
#include "InterfaceOutlet.h"
namespace Uber {
    SliderBlock::SliderBlock()
    :InterfaceBlock()
    ,m_Minimum(0.f)
    ,m_Maximum(5.f)
    ,m_Step(0.05f)
    {
        initialize();
    }

    SliderBlock::~SliderBlock()
    {

    }

    void    SliderBlock::initialize()
    {
        InterfaceOutlet *currentOutlet( new InterfaceOutlet());
        appendOutlet(currentOutlet);
        QObject::connect(this, SIGNAL(valueChanged(QVariant)),
                         currentOutlet, SIGNAL(valueChanged(QVariant)));
    }

    void    SliderBlock::setMinimum( float m )
    {
        m_Minimum = m;
    }

    float   SliderBlock::getMinimum() const
    {
        return m_Minimum;
    }

    void    SliderBlock::setMaximum( float m )
    {
        m_Maximum = m;
    }

    float   SliderBlock::getMaximum() const
    {
        return m_Maximum;
    }
    void    SliderBlock::setStep( float m )
    {
        m_Step = m;
    }

    float   SliderBlock::getStep() const
    {
        return m_Step;
    }

    void SliderBlock::setValue(float value)
    {
        if ( m_Value != value )
        {
            m_Value = value;
            QVariant variantValue(value);
            emit valueChanged(variantValue);
        }
    }

    float SliderBlock::getValue() const
    {
        return m_Value;
    }
    QDebug operator << (QDebug dbg, const SliderBlock &slider )
    {
        Q_UNUSED(slider)
        dbg.nospace() << "SliderBlock";
        return dbg.maybeSpace();
    }
}
