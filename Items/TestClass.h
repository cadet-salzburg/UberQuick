#ifndef TESTCLASS_H
#define TESTCLASS_H
#include "Item.h"
namespace Uber {
class TestClass : public Item
{
    Q_OBJECT
public:
    explicit TestClass(QObject *parent = 0);

signals:

public slots:

};
}
#endif // TESTCLASS_H
