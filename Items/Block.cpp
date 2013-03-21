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

    void    Block::setName( QString name )
    {
        m_Name = name;
    }

    QString Block::getName()
    {
        return m_Name;
    }

    QDebug operator<<(QDebug dbg, const Block &block )
    {
        dbg.nospace() << "Block";
        return dbg.maybeSpace();
    }
}
