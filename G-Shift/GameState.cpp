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
    pressA = false;
    pressS = false;
    pressLShift = false;
    pressSpace = false;
    mousePressed = false;
    index = -1;
}

void GameState::update(float dt, float u, float v)
{
    if(isReady)
    {

        pressA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        pressS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        pressSpace = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        sf::Packet toSend;
        toSend << pressA << pressS << pressSpace << pressLShift << mousePressed << u << v;
        client.send(toSend);

        pressLShift = false;
        mousePressed = false;

    } else {
        if(client.getRemoteAddress()!=sf::IpAddress::None)
        {
            sf::Packet packet;
            client.receive(packet);
            packet >> isReady;
            packet >> index;
            packet >> players;
            renderer.setIndex(index);
            renderer.setN(players);
            client.setBlocking(true);

            sf::Packet toSend;
            toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::A); // LEFT
            toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::S); //RIGHT
            toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::Space); // RISE
            toSend << sf::Keyboard::isKeyPressed(sf::Keyboard::LShift); // Shift
            toSend << sf::Mouse::isButtonPressed(sf::Mouse::Left); // SHOOTING
            toSend << u << v; // mouse pointer coordinate
            client.send(toSend);
        }
    }

}

void GameState::draw(sf::RenderWindow& window)
{

    if(isReady)
    {

        sf::Packet toGet;
        client.receive(toGet);

        for(int i=0; i<players; i++)
        {
            float pX, pY, bX, bY, deg;
            toGet >> pX >> pY >> deg >> bX >> bY;
            renderer.setDeg(i, deg);
            renderer.setPlayerPosition(i, pX, pY);
            renderer.setBulletPosition(i, bX, bY);
        }

        renderer.draw(window);

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
    if(isReady)
    {
        mousePressed = true;
    }
}

void GameState::onKeyReleased(sf::Event e)
{
    if(isReady)
    {
        if(e.key.code == sf::Keyboard::LShift)
            pressLShift = true;
    }
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
        players = 1;
        if(play[2] == '2') players = 2;
        else if (play[2] == '3') players = 3;
        else if (play[2] == '4') players = 4;

        gs.reset();
        gs.setClientNumber(players);
        game_thread.launch();
    }

    ip = sf::IpAddress(ipString);
    client.connect(ip, 53000);
}

GameServer* GameState::getServer()
{
    return &gs;
}

void GameState::onDeactivate()
{
    isReady = false;
    index = -1;
}
