#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Button
{
private:
    bool hover;
    sf::Texture hoverTexture;
    sf::Texture texture;
    Vec2 center;
    Vec2 half_diagonal;
public:
    Button();
    bool checkCollision(float, float);
    void draw(sf::RenderWindow&);
    void update(float, float);
    void setTexture(std::string, std::string);
    void setPosition(float, float);
    void setDimension(float, float);
};

#endif // BUTTON_H_INCLUDED
