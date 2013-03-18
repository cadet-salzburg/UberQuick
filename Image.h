#ifndef IMAGE_H
#define IMAGE_H

#include <QDebug>
#include <QMetaType>
#include "_2RealDatatypes.h"
namespace Uber {
    class _2Real::Image;
    class Image
    {
    public:
        Image();
        Image( const Image &other);
        Image(const _2Real::Image &image);
        ~Image();
        const unsigned char*    getData() const;
    private:
        _2Real::Image           m_Image;
    };
    QDebug operator<<(QDebug dbg, const Image &image);
    Q_DECLARE_METATYPE(Image)
}
#endif // IMAGE_H
