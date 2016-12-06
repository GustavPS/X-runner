#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"

class Block : public Object
{
    public:
        Block(const sf::Vector2f&, const sf::Vector2f&, const std::string&);
        void iamnull() {}
};

#endif