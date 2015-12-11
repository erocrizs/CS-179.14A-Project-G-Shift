#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Block {
private:
    sf::Texture texture;
public:
    Vec2 position;
    bool active;
    Block();
    void draw(sf::RenderWindow&);
};

#endif // BLOCK_H_INCLUDED
