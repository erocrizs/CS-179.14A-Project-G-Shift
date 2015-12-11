#include "Block.h"

Block::Block()
{
    texture.loadFromFile("asset/sprites/block.png");
    active = false;
}

void Block::draw(sf::RenderWindow& window)
{
    if(!active) return;
    sf::Sprite block;
    block.setTexture(texture);
    block.setPosition(position.getX(), position.getY());
    window.draw(block);
};
