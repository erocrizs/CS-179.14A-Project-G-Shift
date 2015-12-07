#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "State.h"
#include "Splash.h"

Splash::Splash()
{
    isFadingIn = false;
    isOnPause = false;
    isFadingOut = false;
    timeCount = 0;
    logoAlpha = 0;
}

void Splash::update(float dt)
{
    std::cout << logoAlpha << " " << timeCount << std::endl;
    if(isFadingIn || isFadingOut || isOnPause)
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
            int newAlpha = logoAlpha+(int)(255*dt);
            logoAlpha = std::min(newAlpha, 255);
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
            int newAlpha = logoAlpha-(int)(255*dt);
            logoAlpha = std::max(newAlpha, 0);
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
