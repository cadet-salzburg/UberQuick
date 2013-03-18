#include "Image.h"

namespace Uber
{
    Image::Image()
    {

    }

    Image::Image( const Image &other )
    {
        m_Image = _2Real::Image( const_cast<unsigned char*>(other.getData()), false, 640, 480, _2Real::ImageChannelOrder::RGB );
    }

    Image::Image(const _2Real::Image &image)
    {
        m_Image = image;
    }

    Image::~Image()
    {

    }

    const unsigned char* Image::getData() const
    {
        return m_Image.getData();
    }

    QDebug operator<<(QDebug dbg, const Image &image )
    {
        dbg.nospace() << "UbImage()";
        return dbg.maybeSpace();
    }
}
