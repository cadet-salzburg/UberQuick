#include "StringObject.h"
namespace Uber {
    StringObject::StringObject(QObject *parent)
    :QObject(parent)
    {
    }
    QString StringObject::getString()
    {
        return m_String;
    }
    void StringObject::setString(const QString &string )
    {
        m_String = string;
    }
}
