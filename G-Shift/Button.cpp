#include <SFML/Graphics.hpp>
#include "Button.h"
#include <stdlib.h>
#include <iostream>

bool Button::checkCollision(float u, float v)
{
    float targetX = clamp(u, center.getX()-half_diagonal.getX(), center.getX()+half_diagonal.getX());
    float targetY = clamp(v, center.getY()-half_diagonal.getY(), center.getY()+half_diagonal.getY());
    hover = (targetX==u && targetY==v);
    return hover;
}

void Button::draw(sf::RenderWindow& window)
{
    sf::Texture* show;
    if(hover)
        show = &hoverTexture;
    else
        show = &texture;

    sf::Sprite button_sprite;
    button_sprite.setTexture((*show));
    float drawPosX = center.getX()-half_diagonal.getX();
    float drawPosY = center.getY()-half_diagonal.getY();
    button_sprite.setPosition(drawPosX, drawPosY);
    window.draw(button_sprite);
}

void Button::setTexture(std::string ad, std::string had)
{
    texture.loadFromFile(ad, sf::IntRect(0, 0, 0, 0));
    hoverTexture.loadFromFile(had, sf::IntRect(0, 0, 0, 0));
}

void Button::setPosition(float u, float v)
{
    center = Vec2(u, v);
}

void Button::setDimension(float u, float v)
{
    half_diagonal = Vec2(u/2.0, v/2.0);
}
