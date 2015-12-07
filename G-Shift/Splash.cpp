#include <SFML/Graphics.hpp>
#include "State.h"
#include "Splash.h"

Splash::Splash()
{
    bool isFadingIn = false;
    bool isOnPause = false;
    bool isFadingOut = false;
    float timeCount = 0;
    unsigned int logoAlpha = 0;
}

void Splash::update(float dt)
{
    timeCount += dt;
    if(isFadingIn)
    {
        if(timeCount>=1)
        {
            timeCount -= 1;
            logoAlpha = 255;
            isFadingIn = false;
            isOnPause = true;
            isFadingOut = false;
        }
        else
        {
            logoAlpha += (unsigned int)(255*dt);
        }
    }
    else if(isOnPause)
    {
        if(timeCount>=1)
        {
            timeCount -= 1;
            logoAlpha -= (255*timeCount);
            isFadingIn = false;
            isFadingOut = true;
            isOnPause = false;
        }
    }
    else if(isFadingOut)
    {
        if(timeCount>=1)
        {
            logoAlpha = 0;
        }
        else
        {
            logoAlpha -= (255*dt);
        }
    }
}

void Splash::draw(sf::RenderWindow& window)
{
    sf::Vector2f size(100, 100);
    sf::RectangleShape rect(size);
    rect.setPosition(100, 100);
    sf::Color rectColor(255, 255, 255, logoAlpha);
    rect.setFillColor(rectColor);
    window.draw(rect);
}

void Splash::onActivate()
{
    isFadingIn = true;
}
