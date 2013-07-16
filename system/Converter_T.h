#ifndef CONVERTER_T_H
#define CONVERTER_T_H
#include "Converter.h"

namespace Uber {

template <class TType>
class Converter_T;

template < >
class Converter_T< int > {
    void set( _2Real::CustomType& value, const QString& field, float& v )
    {
        value.set<int>( field.toUtf8().constData(), static_cast<int>(v) );
    }
};

template < >
class Converter_T< short > {
    void set( _2Real::CustomType& value, const QString& field, float& v )
    {
        value.set<short>( field.toUtf8().constData(), static_cast<short>(v) );
    }
};

template < >
class Converter_T< double > {
    void set( _2Real::CustomType& value, const QString& field, float& v )
    {
        value.set<double>( field.toUtf8().constData(), static_cast<double>(v) );
    }
};

template <class TType>
class Converter_T {
    void set( _2Real::CustomType& value, const QString& field, const float& v )
    {
        throw std::runtime_error("Cannot convert to sepcified type");
    }
};

}
#endif // CONVERTER_T_H
