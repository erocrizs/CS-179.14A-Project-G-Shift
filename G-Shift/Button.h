#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Button
{
private:
    bool hover;
    std::string content;
    unsigned int fontHeight;
    sf::Font font;
    sf::Text label;
    Vec2 center;
    Vec2 half_diagonal;
public:
    Button();
    bool checkCollision(float, float);
    void draw(sf::RenderWindow&);
    void setPosition(float, float);
    void setDimension(float, float);
    void setContent(std::string);
};

#endif // BUTTON_H_INCLUDED
