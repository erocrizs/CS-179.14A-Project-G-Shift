#include "MenuScreen.h"
#include "State.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

MenuScreen::MenuScreen()
{
	host.setContent("Host Game");
	host.setPosition(400, 400);
	host.setDimension(270, 40);

	join.setContent("Join Game");
	join.setPosition(400, 450);
	join.setDimension(270, 40);

	logoTexture.loadFromFile("asset/sprites/game-logo.png", sf::IntRect(0, 0, 0, 0));

    cover = 255;
}

void MenuScreen::update(float dt, float u, float v)
{
    bool hostCheck = host.checkCollision(u, v);
    bool joinCheck = join.checkCollision(u, v);

    if(cover==0) return;
    int temp = cover - (255*dt);
    cover = std::max(temp, 0);
}

void MenuScreen::draw(sf::RenderWindow& window)
{
    sf::Sprite gameLogo;
	gameLogo.setTexture(logoTexture);
    gameLogo.setPosition(100, 150);

    window.draw(gameLogo);
    host.draw(window);
    join.draw(window);

    if(cover==0) return;
    sf::Vector2f curtainSize(800, 600);
    sf::RectangleShape curtain(curtainSize);
    curtain.setPosition(0, 0);
    curtain.setFillColor(sf::Color(0, 0, 0, cover));
    window.draw(curtain);
}

void MenuScreen::onClick(float u, float v)
{
    if(cover>0)
    {
        cover = 0;
        return;
    }
}
