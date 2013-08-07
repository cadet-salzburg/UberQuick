#ifndef SLIDER_H
#define SLIDER_H
#include <QVariant>
#include "InterfaceElement.h"
namespace Uber {
class Slider : public InterfaceElement
{
    Q_OBJECT
    Q_PROPERTY( float minimum READ getMinimum WRITE setMinimum NOTIFY minimumChanged )
    Q_PROPERTY( float maximum READ getMaximum WRITE setMaximum NOTIFY maximumChanged )
    Q_PROPERTY( float step READ getStep WRITE setStep NOTIFY stepChanged )
    Q_PROPERTY( float value READ getValue WRITE setValue NOTIFY valueChanged )
public:
    Slider();
    virtual         ~Slider();
    void            setMinimum( float m );
    float           getMinimum() const;

    void            setMaximum( float m );
    float           getMaximum() const;

    void            setStep( float offset );
    float           getStep() const;

    void            setValue( float value );
    float           getValue() const;
signals:
    void            valueChanged(QVariant newValue);
    void            minimumChanged();
    void            maximumChanged();
    void            stepChanged();
private:
    float           m_Minimum;
    float           m_Maximum;
    float           m_Step;
    float           m_Value;

    void            initialize();
};
    QDebug operator<<(QDebug dbg, const Slider &slider);
}
#endif // SLIDER_H
