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

    levelFile.loadFromFile("asset/levels/stage1.png");
    for(int x = 0; x<40; x++)
    {
        for(int y=0; y<21; y++)
        {
            blockList[x][y].position = Vec2(x*40,y*40);
            blockList[x][y].active = levelFile.getPixel(x, y)==sf::Color::Black;
        }
    }
}

void GameState::update(float dt, float u, float v)
{
    if(isReady)
    {
        sf::Packet toSend;

        toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        toSend << sf::Mouse::isButtonPressed(sf::Mouse::Left);
        toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
        toSend << u;
        toSend << v;

        client.send(toSend);

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
        for(int i=0; i<40; i++) {
            for(int j=0; j<21; j++) {
                Vec2 pos = blockList[i][j].position;
                if(clamp(pos.getX(),-40, 840)==pos.getX() && clamp(pos.getY(), -40, 640)==pos.getY())
                    blockList[i][j].draw(window);
            }
        }
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
        player = 1;
        if(play[2] == '2') player = 2;
        else if (play[2] == '3') player = 3;
        else if (play[2] == '4') player = 4;

        gs.reset();
        gs.setClientNumber(player);
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
    player = 0;
}
