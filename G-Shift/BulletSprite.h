#ifndef BULLETSPRITE_H_INCLUDED
#define BULLETSPRITE_H_INCLUDED
#include "Vec2.h"
#include <SFML/Graphics.hpp>

class BulletSprite {
private:
    Vec2 position;
    sf::CircleShape cs;
    float rad;
public:
    BulletSprite() {
        position = Vec2(0, 0);
        rad = 10;
        cs.setRadius(rad);
        cs.setOrigin(rad, rad);
    };
    void draw(sf::RenderTarget& rt, sf::Color c, Vec2 relative) {
        Vec2 pos = position + relative;
        cs.setFillColor(c);
        cs.setPosition(position.getX(), position.getY());
        rt.draw(cs);
    }
    void setPosition(float a, float b) {
        position = Vec2(a, b);
    }
    Vec2 getPosition()
    {
        return position;
    }
};


#endif // BULLETSPRITE_H_INCLUDED
