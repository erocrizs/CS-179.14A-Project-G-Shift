#include "HostState.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

HostState::HostState()
{
	twoPlayer.setContent("2 Players");
	twoPlayer.setPosition(400, 250);
	twoPlayer.setDimension(225, 35);

	threePlayer.setContent("3 Players");
	threePlayer.setPosition(400, 300);
	threePlayer.setDimension(225, 35);

	fourPlayer.setContent("4 Players");
	fourPlayer.setPosition(400, 350);
	fourPlayer.setDimension(225, 35);

	back.setContent("Back");
	back.setPosition(150, 550);
	back.setDimension(200, 35);
    font.loadFromFile("asset/fonts/8-BIT WONDER.TTF");
}

void HostState::update(float dt, float u, float v)
{
    back.checkCollision(u, v);
    twoPlayer.checkCollision(u, v);
    threePlayer.checkCollision(u, v);
    fourPlayer.checkCollision(u, v);
}

void HostState::draw(sf::RenderWindow& window)
{
    sf::Text header("Select number of players", font);
    header.setColor(sf::Color::White);
    float headerW = header.getLocalBounds().width;
    float headerH = header.getLocalBounds().height;
    header.setOrigin(headerW/2, headerH/2);
    header.setPosition(400, 100);

    window.draw(header);
    twoPlayer.draw(window);
    threePlayer.draw(window);
    fourPlayer.draw(window);
    back.draw(window);
}

void HostState::onClick(float u, float v)
{
    if(back.checkCollision(u, v))
    {
        manager->pop(1);
    }
}
