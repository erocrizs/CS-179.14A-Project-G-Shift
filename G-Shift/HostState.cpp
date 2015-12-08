#include "HostState.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

HostState::HostState()
{
	twoPlayer.setContent("2 Players");
	twoPlayer.setPosition(400, 250);
	twoPlayer.setDimension(200, 30);

	threePlayer.setContent("3 Players");
	threePlayer.setPosition(400, 300);
	threePlayer.setDimension(200, 30);

	fourPlayer.setContent("4 Players");
	fourPlayer.setPosition(400, 350);
	fourPlayer.setDimension(200, 30);

	back.setContent("Back");
	back.setPosition(150, 550);
	back.setDimension(200, 30);
    font.loadFromFile("asset/fonts/PressStart2P.ttf");
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
    else if(twoPlayer.checkCollision(u, v))
    {
        manager->push(3, "2");
    }
}
