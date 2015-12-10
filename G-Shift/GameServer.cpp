#include "GameServer.h"
#include <iostream>

GameServer::GameServer()
{
    reset();
}

void GameServer::reset()
{
    clientNumber = 0;
    joinedNumber = 0;
    timesUp = false;
}

void GameServer::setClientNumber(int i)
{
    clientNumber = i;
}

void GameServer::timeFinish()
{
    timesUp = true;
}

void GameServer::start_server()
{
    sf::Packet connectNotif;
    connectNotif << "Connected";

    while(joinedNumber < clientNumber)
    {
        sf::TcpListener listener;
        listener.listen(53000);
        listener.accept(clients[joinedNumber]);
        clients[joinedNumber].send(connectNotif);
        std::cout << joinedNumber << " : " << clientNumber << std::endl;
        joinedNumber++;
    }
    std::cout << "someone connected" << std::endl;

    while(!timesUp)
    {
        std::string s;
        sf::Packet receivePacket;
        for(int i=0; i<clientNumber; i++)
        {
            clients[i].receive(receivePacket);
            // do stuff
        }

        // random stuff

        sf::Packet sendPacket;
        sendPacket << "Quando";
        for(int i=0; i<clientNumber; i++)
            clients[i].send(sendPacket);
    }

}
