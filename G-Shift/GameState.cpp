#include "GameState.h"
#include "StateManager.h"
#include <SFML/Network.hpp>

GameState::GameState()
{
	back.setContent("Back");
	back.setPosition(150, 550);
	back.setDimension(200, 35);
    font.loadFromFile("asset/fonts/8-BIT WONDER.TTF");
}

void GameState::update(float dt, float u, float v)
{
    back.checkCollision(u, v);
}

void GameState::draw(sf::RenderWindow& window)
{
    sf::IpAddress localhost = sf::IpAddress::getLocalAddress();
    sf::Text header("Your IP Address: " + localhost.toString(), font, 20);
    header.setColor(sf::Color::White);
    float headerW = header.getLocalBounds().width;
    float headerH = header.getLocalBounds().height;
    header.setOrigin(headerW/2, headerH/2);
    header.setPosition(400, 100);

    window.draw(header);
    back.draw(window);
}
