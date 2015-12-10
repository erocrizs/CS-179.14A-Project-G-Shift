#include "GameState.h"
#include "StateManager.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <list>
#include <string.h>

void allowConnections();
void connectTo(std::string a);
sf::TcpSocket socket;
int numPlayers;
int players;
sf::TcpListener listener;
sf::SocketSelector selector;
sf::Text taking;
std::list<sf::Packet> coords;

GameState::GameState()
{
	back.setContent("Back");
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
    sf::IpAddress localhost = sf::IpAddress::getLocalAddress();
    sf::Text header("Your IP Address: " + localhost.toString(), font, 20);
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

void GameState::onActivate()
{
    numPlayers++;
}

void GameState::onClick(float u, float v)
{
    if(back.checkCollision(u, v))
    {
        manager->pop(1);
    }
}


void GameState::pass(std::string play)
{
    std::cout << "tell me when will you be mine~~~" << std::endl;
    if(play[0]=='c')
    {
        std::cout << "tell me quando quando quandoo~~~" << std::endl;
        std::string ip = play.substr(2, play.size());
        std::cout << "MUDA" << std::endl;
        connectTo(ip);
    }
    else if(play[0]=='h')
    {
         std::cout << "STAHP" << std::endl;
         std::string m = play.substr(2, 2);
         if(m == "2") players = 2;
         else if (m == "3") players = 3;
         else if (m == "4") players = 4;
         allowConnections();
    }

}


void allowConnections(){
    std::cout<< "Initiating server" << std::endl;
    std::cout << players << " PLAYAHS ALLOWED" <<std::endl;
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
