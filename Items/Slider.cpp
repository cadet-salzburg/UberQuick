#include "Slider.h"
#include <QDebug>
#include "InterfaceOutlet.h"
namespace Uber {
    Slider::Slider()
    :InterfaceElement()
    ,m_Minimum(0.f)
    ,m_Maximum(5.f)
    ,m_Step(0.05f)
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
        QObject::connect(this, SIGNAL(valueChanged(QVariant)),
                         currentOutlet, SLOT(valueChanged(QVariant)));
    }

    void    Slider::setMinimum( float m )
    {
        m_Minimum = m;
    }

    float   Slider::getMinimum() const
    {
        return m_Minimum;
    }

    void    Slider::setMaximum( float m )
    {
        m_Maximum = m;
    }

    float   Slider::getMaximum() const
    {
        return m_Maximum;
    }
    void    Slider::setStep( float m )
    {
        m_Step = m;
    }

    float   Slider::getStep() const
    {
        return m_Step;
    }

    void Slider::setValue(float value)
    {
        if ( m_Value != value )
        {
            m_Value = value;
            QVariant variantValue(value);
            emit valueChanged(variantValue);
        }
        qDebug() << " Slider value: " << m_Value;
    }

    float Slider::getValue() const
    {
        return m_Value;
    }
    QDebug operator << (QDebug dbg, const Slider &slider )
    {
        Q_UNUSED(slider)
        dbg.nospace() << "Slider";
        return dbg.maybeSpace();
    }
}
