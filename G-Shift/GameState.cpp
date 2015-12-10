#include "GameState.h"
#include "GameServer.h"
#include "StateManager.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <list>
#include <string.h>

void allowConnections();
void connectTo(std::string a);

GameState::GameState(): game_thread(&GameServer::start_server, &gs)
{
    client.setBlocking(false);
    font.loadFromFile("asset/fonts/PressStart2P.ttf");
    isReady = false;
}

void GameState::update(float dt, float u, float v)
{
    if(isReady)
    {
        sf::Packet toSend;
        client.send(toSend);

        //TODO

        sf::Packet toGet;
        client.receive(toGet);

    } else {
        if(client.getRemoteAddress()!=sf::IpAddress::None)
        {
            sf::Packet packet;
            client.receive(packet);
            packet >> isReady;
        }
    }

}

void GameState::draw(sf::RenderWindow& window)
{
    if(isReady)
    {
        // TODO
    } else
    {
        std::string message = "Connecting...";
        if(isHost)
        {
            message = "Your IP Address: " + sf::IpAddress::getLocalAddress().toString();
        }
        sf::Text header(message, font, 20);
        header.setColor(sf::Color::White);
        float headerW = header.getLocalBounds().width;
        float headerH = header.getLocalBounds().height;
        header.setOrigin(headerW/2, headerH/2);
        header.setPosition(400, 100);

        window.draw(header);

    }
}

void GameState::onClick(float u, float v)
{
}

void GameState::gameReady()
{
    isReady = true;
}

void GameState::pass(std::string play)
{
    std::string ipString = "localhost";
    isHost = (play[0]=='h');
    if(play[0]=='c')
    {
        ipString = play.substr(2);
    }
    else if(play[0]=='h')
    {
        int players = 1;
        if(play[2] == '2') players = 2;
        else if (play[2] == '3') players = 3;
        else if (play[2] == '4') players = 4;

        gs.reset();
        gs.setClientNumber(players);
        game_thread.launch();
    }

    ip = sf::IpAddress(ipString);
    client.setBlocking(false);
    client.connect(ip, 53000);
    std::cout << "awesome" << std::endl;
}

GameServer* GameState::getServer()
{
    return &gs;
}

void GameState::onDeactivate()
{
    isReady = false;
}
