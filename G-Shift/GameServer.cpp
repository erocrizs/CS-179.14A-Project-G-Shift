#include "GameServer.h"
#include <iostream>

GameServer::GameServer()
{
    clientNumber = 0;
    joinedNumber = 0;
    reset();
}

void GameServer::reset()
{
    listener.close();
    for(int i=0; i<clientNumber; i++)
    {
        if(clients[i].getRemoteAddress()!=sf::IpAddress::None)
            clients[i].disconnect();
    }
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
    connectNotif << true;
    while(joinedNumber < clientNumber)
    {
        listener.close();
        listener.listen(53000);
        listener.accept(clients[joinedNumber]);
        if(clients[joinedNumber].getRemoteAddress()!= sf::IpAddress::None)
            joinedNumber++;
    }

    for(int i=0; i<clientNumber; i++)
    {
        clients[i].send(connectNotif);
    }

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

void GameServer::setGameState(GameState* state)
{
    gs = state;
}
