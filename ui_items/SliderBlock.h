#ifndef SLIDERBLOCK_H
#define SLIDERBLOCK_H
#include <QVariant>
#include "InterfaceBlock.h"
namespace Uber {
class SliderBlock : public InterfaceBlock
{
    Q_OBJECT
    Q_PROPERTY( float minimum READ getMinimum WRITE setMinimum NOTIFY minimumChanged )
    Q_PROPERTY( float maximum READ getMaximum WRITE setMaximum NOTIFY maximumChanged )
    Q_PROPERTY( float step READ getStep WRITE setStep NOTIFY stepChanged )
    Q_PROPERTY( float value READ getValue WRITE setValue NOTIFY valueChanged )
public:
    SliderBlock();
    virtual         ~SliderBlock();
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
    QDebug operator<<(QDebug dbg, const SliderBlock &slider);
}
#endif // SLIDERBLOCK_H
