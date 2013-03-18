#include "Block.h"
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
}
