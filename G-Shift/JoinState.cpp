#include "GameState.h"
#include "StateManager.h"
#include <SFML/Network.hpp>
#include "State.h"
#include "JoinState.h"
#include <iostream>

std::string str = "";
sf::String in;
void connectTo(std::string a);


JoinState::JoinState()
{
	back.setContent("Back");
	back.setPosition(150, 550);
	back.setDimension(200, 35);

    forth.setContent("Join");
	forth.setPosition(650, 550);
	forth.setDimension(200, 35);
    font.loadFromFile("asset/fonts/PressStart2P.ttf");
}

void JoinState::update(float dt, float u, float v)
{
    back.checkCollision(u, v);
    forth.checkCollision(u, v);
}



void JoinState::draw(sf::RenderWindow& window)
{
    sf::IpAddress localhost = sf::IpAddress::getLocalAddress();
    sf::Text header("Your IP Address: " + localhost.toString(), font, 20);
    header.setColor(sf::Color::White);
    float headerW = header.getLocalBounds().width;
    float headerH = header.getLocalBounds().height;
    header.setOrigin(headerW/2, headerH/2);
    header.setPosition(400, 100);

    sf::Text connect("Host IP Address: ", font, 20);
    connect.setPosition(50, 400);

    sf::Text input;
    input.setPosition(400, 400);
    input.setFont(font);
    input.setCharacterSize(20);
    input.setString(str);

    window.draw(header);
    window.draw(input);
    window.draw(connect);
    back.draw(window);
    forth.draw(window);
}

void JoinState::onClick(float u, float v)
{
    if(back.checkCollision(u, v))
    {
        manager->pop(1);
    }
    else if(forth.checkCollision(u, v))
    {
        accept();
    }
}

void JoinState::getText(std::string text)
{
    str = text;
    std::cout << str << std::endl;
}

void JoinState::accept()
{
    std::cout << "PANGIT" << std::endl;
    manager->push(3, "c " + str);
}
