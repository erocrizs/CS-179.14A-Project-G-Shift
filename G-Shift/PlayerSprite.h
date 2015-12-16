#ifndef PLAYERSPRITE_H_INCLUDED
#define PLAYERSPRITE_H_INCLUDED
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class PlayerSprite {
private:
    float deg;
    Vec2 position;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    PlayerSprite() {
        deg = 0;
        position = Vec2(0, 0);
    };
    void draw(sf::RenderTarget& rt, sf::Color c) {
        texture.loadFromFile("asset/sprites/chara.png");
        sprite.setTexture(texture);
        sprite.setOrigin(20, 20);
        sprite.setPosition(position.getX(), position.getY());
        sprite.setColor(c);
        sprite.setRotation(deg);
        rt.draw(sprite);
    }
    void setPosition(float a, float b) {
        position = Vec2(a, b);
    }
    Vec2 getPosition() {
        return position;
    }
    void setDeg(float d)
    {
        deg = d;
    }
};

#endif // PLAYERSPRITE_H_INCLUDED
