#ifndef CONVERTER_H
#define CONVERTER_H
#include "_2RealApplication.h"
#include "_2RealDatatypes.h"

#include <QString>
namespace Uber {
class Converter {
    virtual ~Converter();
    virtual set( _2Real::CustomType& value, const QString& field, const float& v) = 0;
};
}
#endif // ABSTRACTCONVERTER_H
