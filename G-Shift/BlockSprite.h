#ifndef BLOCKSPRITE_H_INCLUDED
#define BLOCKSPRITE_H_INCLUDED
#include <SFML/Graphics.hpp>

class BlockSprite {
private:
    Vec2 position;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    BlockSprite() {
        position = Vec2(0, 0);
    };
    void draw(sf::RenderTarget& rt) {
        texture.loadFromFile("asset/sprites/block.png");
        sprite.setTexture(texture);
        sprite.setOrigin(20, 20);
        sprite.setPosition(position.getX(), position.getY());
        rt.draw(sprite);
    }
    void setPosition(float a, float b) {
        position = Vec2(a, b);
    }
    Vec2 getPosition() {
        return position;
    }
};

#endif // BLOCKSPRITE_H_INCLUDED
