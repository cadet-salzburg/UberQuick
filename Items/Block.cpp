#include "Block.h"
#include <QDebug>
namespace Uber {
    Block::Block(QObject *parent)
    :Item(parent)
    {
    }
    Block::Block(const Block &other)
    :Item(other.parent(), other.position(), other.size())
    {
    }
    Block::~Block()
    {

    }
    QDebug operator<<(QDebug dbg, const Block &block )
    {
        dbg.nospace() << "Block";
        return dbg.maybeSpace();
    }
}
