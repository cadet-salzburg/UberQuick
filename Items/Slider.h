#ifndef SLIDER_H
#define SLIDER_H
#include "InterfaceElement.h"
namespace Uber {
class Slider : public InterfaceElement
{
    Q_OBJECT
    Q_PROPERTY( float minimum READ getMinimum WRITE setMinimum NOTIFY minimumChanged )
    Q_PROPERTY( float maximum READ getMaximum WRITE setMaximum NOTIFY maximumChanged )
    Q_PROPERTY( float step READ getStep WRITE setStep NOTIFY stepChanged )
public:
    Slider();
    virtual         ~Slider();
    void            setMinimum( float m );
    float           getMinimum() const;

    void            setMaximum( float m );
    float           getMaximum() const;

    void            setStep( float offset );
    float           getStep() const;
signals:
    void            minimumChanged();
    void            maximumChanged();
    void            stepChanged();
private:
    float           m_Minimum;
    float           m_Maximum;
    float           m_Step;
    virtual void    initialize();
};
    QDebug operator<<(QDebug dbg, const Slider &slider);
}
#endif // SLIDER_H
