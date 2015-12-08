#include <SFML/Graphics.hpp>
#include "Button.h"
#include <stdlib.h>
#include <iostream>

Button::Button()
{
    font.loadFromFile("asset/fonts/8-BIT WONDER.TTF");
}

bool Button::checkCollision(float u, float v)
{
    float targetX = clamp(u, center.getX()-half_diagonal.getX(), center.getX()+half_diagonal.getX());
    float targetY = clamp(v, center.getY()-half_diagonal.getY(), center.getY()+half_diagonal.getY());
    hover = (targetX==u && targetY==v);
    return hover;
}

void Button::draw(sf::RenderWindow& window)
{
    float drawPosX = center.getX()-half_diagonal.getX();
    float drawPosY = center.getY()-half_diagonal.getY();
    float width = half_diagonal.getX()*2;
    float height = half_diagonal.getY()*2;
    unsigned int fontSize = (unsigned int)(height*0.75);
    sf::RectangleShape drop;
    drop.setSize(sf::Vector2f(width, height));
    sf::Text label(content, font, fontSize);

    if(hover)
    {
        label.setColor(sf::Color::Black);
        drop.setFillColor(sf::Color::White);
    }
    else
    {
        label.setColor(sf::Color::White);
        drop.setFillColor(sf::Color(0,0,0,0));
    }
    drop.setPosition(drawPosX, drawPosY);
    label.setPosition(drawPosX+3, drawPosY+3);
    window.draw(drop);
    window.draw(label);
}

void Button::setPosition(float u, float v)
{
    center = Vec2(u, v);
}

void Button::setDimension(float u, float v)
{
    half_diagonal = Vec2(u/2.0, v/2.0);
}

void Button::setContent(const std::string cont)
{
    content = cont;
}
