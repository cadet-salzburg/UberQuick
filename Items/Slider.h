#ifndef SLIDER_H
#define SLIDER_H
#include "Item.h"
namespace Uber {
class Slider : public Item
{
    Q_OBJECT
    Q_PROPERTY( float multiplier READ getMultiplier WRITE setMultiplier NOTIFY multiplierChanged )
    Q_PROPERTY( float offset READ getOffset WRITE setOffset NOTIFY offsetChanged )
public:
    Slider();
    ~Slider();
    void    setMultiplier( float m );
    float   getMultiplier() const;
    void    setOffset( float offset );
    float   getOffset() const;
signals:
    void    multiplierChanged();
    void    offsetChanged();
private:
    float   m_Multiplier;
    float   m_Offset;
};
    QDebug operator<<(QDebug dbg, const Slider &slider);
}
#endif // SLIDER_H
