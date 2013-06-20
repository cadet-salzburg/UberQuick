#ifndef SLIDER_H
#define SLIDER_H
#include "InterfaceElement.h"
namespace Uber {
class Slider : public InterfaceElement
{
    Q_OBJECT
    Q_PROPERTY( float multiplier READ getMultiplier WRITE setMultiplier NOTIFY multiplierChanged )
    Q_PROPERTY( float offset READ getOffset WRITE setOffset NOTIFY offsetChanged )
public:
    Slider();
    virtual         ~Slider();
    void            setMultiplier( float m );
    float           getMultiplier() const;
    void            setOffset( float offset );
    float           getOffset() const;
signals:
    void            multiplierChanged();
    void            offsetChanged();
private:
    float           m_Multiplier;
    float           m_Offset;
    virtual void    initialize();
};
    QDebug operator<<(QDebug dbg, const Slider &slider);
}
#endif // SLIDER_H
