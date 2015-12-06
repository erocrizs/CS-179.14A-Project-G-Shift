#include <SFML/Network.hpp>
#include <iostream>
#include <list>
int main()
{
    sf::TcpListener listener;
    listener.listen(53000);

    std::list<sf::TcpSocket*> clients;

    sf::SocketSelector selector;

    selector.add(listener);

    while(true)
    {
        if(selector.wait())
        {
            if(selector.isReady(listener))
            {
                sf::TcpSocket* client = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(client);

                    selector.add(*client);
                }

                else
                {
                    delete client;
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
                            std::string g;
                            packet >> g;

                            std::cout<< g <<std::endl;
                        }
                    }
                }
            }
        }
    }
}
