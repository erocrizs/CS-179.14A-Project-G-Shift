#include "GameState.h"
#include "StateManager.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <list>
#include <string.h>

void allowConnections();
void connectTo(std::string a);

GameState::GameState(): game_thread(&GameServer::start_server, &gs)
{
	back.setContent("Cancel");
	back.setPosition(150, 550);
	back.setDimension(200, 35);
    font.loadFromFile("asset/fonts/PressStart2P.ttf");
}

void GameState::update(float dt, float u, float v)
{
    back.checkCollision(u, v);
}

void GameState::draw(sf::RenderWindow& window)
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

    taking.setColor(sf::Color::White);
    taking.setPosition(50, 100);

    window.draw(header);
    window.draw(taking);
    back.draw(window);
}

void GameState::onClick(float u, float v)
{
    if(back.checkCollision(u, v))
    {
        gs.timeFinish();
        game_thread.wait();
        manager->pop(1);
    }
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
    client.connect(ip, 53000);
    sf::Packet packet;
    client.receive(packet);
    std::string s;
    packet >> s;
    std::cout << s << "awesome" << std::endl;
}

GameServer* GameState::getServer()
{
    return &gs;
}

/*
void allowConnections(){
    std::list<sf::TcpSocket*> clients;
    listener.listen(53000);
    selector.add(listener);
    while(true){
        if(selector.wait())
        {
            if(selector.isReady(listener))
            {
                sf::TcpSocket* socket = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                listener.accept(*socket);
                clients.push_back(socket);
                selector.add(*socket);
                numPlayers++;
                std::cout << "new player connected. Number players: " << numPlayers << std::endl;

                if (numPlayers == players)
                {
                     std::cout << numPlayers << " players connected, not more allowed." << std::endl;
                     selector.remove(listener);
                     listener.close();
                }
            }

            else
            {
                for(std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;
                    if(selector.isReady(client))
                    {
                        sf::Packet packet;
                        if(client.receive(packet) == sf::Socket::Done)
                        {
                           coords.push_back(packet);
                        }
                    }
                }
                for(std::list<sf::Packet>::iterator it = coords.begin(); it != coords.end(); ++it)
                {

                }
                //unloading stuff
                //computing stuff
                //send back
            }
        }
    }
}

void connectTo(std::string a){
    sf::Socket::Status status = socket.connect(a, 53000);
    if(status != sf::Socket::Done)
    {
        std::cout << "Not Connected" <<std::endl;
    }
    else
    {
        std::cout << "Connected" <<std::endl;
    }
}
*/
