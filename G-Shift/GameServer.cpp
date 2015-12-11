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
            Player curr = player[i];
            clients[i].receive(receivePacket);
            bool left;
            bool right;
            bool shoot;
            bool shift;
            bool jump;
            float mouseX;
            float mouseY;
            receivePacket >> left >> right >> jump >> shoot >> shift >> mouseX >> mouseY;
            if(shoot && bullet[i].isActive()){
                bullet[i].activate(true);
                bullet[i].setVelocity(mouseX, mouseY);
                bullet[i].setCoords(curr.getPosition());
            } if(jump && !curr.isJumping())
            {
                jump = true;
            }
            if(curr.isJumping())
            {
                curr.jumpUp(1.0/30);
            } else {
                curr.fall(1.0/30);
            }
            if(left)
                curr.move(-1, 1.0/30);
            else if(right)
                curr.move(1, 1.0/30);
            if(shift){
                curr.setOrientation(((curr.getOrientation()+1)%4) + 1);
            }
        }

        sf::Packet sendPacket;
        sendPacket << clientNumber;

        for(int i=0; i<clientNumber; i++){

        }
    }

}

void GameServer::setGameState(GameState* state)
{
    gs = state;
}
