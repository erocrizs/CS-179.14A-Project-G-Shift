#include "GameServer.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "Vec2.h"

GameServer::GameServer()
{
    clientNumber = 0;
    joinedNumber = 0;
    level.loadFromFile("asset/levels/stage1.png");
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

    while(joinedNumber < clientNumber)
    {
        listener.close();
        listener.listen(53000);
        listener.accept(clients[joinedNumber]);
        if(clients[joinedNumber].getRemoteAddress()!= sf::IpAddress::None)
        {
            joinedNumber++;
        }
    }

    for(int i=0; i<clientNumber; i++)
    {
        sf::Packet connectNotif;
        connectNotif << true << i << clientNumber;
        clients[i].send(connectNotif);
        bullet[i].setIndex(i);
    }


    float dt = 1.0/30;

    int spawn = 0;
    for(int i=0; i<40; i++)
    {
        for(int j=0; j<21; j++)
        {
            if(level.getPixel(i, j)==sf::Color::Red)
            {
                Vec2 pos((i*40)+20, (j*40)+20);
                player[spawn].setPosition(pos);
                spawn++;
            }
        }
    }

    while(!timesUp)
    {

        for(int i=0; i<clientNumber; i++)
        {

            sf::Packet receivePacket;
            clients[i].receive(receivePacket);
            bool left, right, rise, shift, shoot;
            float u, v;

            receivePacket >> left >> right >> rise >> shift >> shoot >> u >> v;
            Vec2 playPos = player[i].getPos();
            int initX, initY, endX, endY;

            // Left and Right Movements
            initX = floor(playPos.getX()/40.0);
            initY = floor(playPos.getY()/40.0);

            Vec2 horizontalDisp = player[i].getHorizontalVel()*dt;
            if(!(left ^ right))
                horizontalDisp = Vec2(0, 0);
            else if(left)
                horizontalDisp = horizontalDisp*-1;
            playPos = playPos + horizontalDisp;

            endX = floor(playPos.getX()/40.0);
            endY = floor(playPos.getY()/40.0);

            // Collision check
            // TODO

            // Gravity Movement

            // integrate gravity
            initX = endX;
            initY = endY;

            Vec2 verticalVelocity = player[i].getFallVel();
            Vec2 addedVelocity = player[i].getAcc()*dt;
            if(rise)
                addedVelocity = addedVelocity*-1;
            verticalVelocity = verticalVelocity + addedVelocity;
            std::cout << verticalVelocity.magnitude() << std::endl;
            if(verticalVelocity.magnitude()>700){
                float xMag = std::min(700.0f, std::abs(verticalVelocity.getX()));
                float yMag = std::min(700.0f, std::abs(verticalVelocity.getY()));
                float xSign = 1, ySign = 1;
                if(verticalVelocity.getX()<0) xSign = -1;
                if(verticalVelocity.getY()<0) ySign = -1;
                verticalVelocity = Vec2(xMag*xSign, yMag*ySign);
            }

            Vec2 verticalDisp = verticalVelocity*dt;
            player[i].setFallVelocity(verticalVelocity);
            playPos = playPos + verticalDisp;

            endX = floor(playPos.getX()/40.0);
            endY = floor(playPos.getY()/40.0);


            // Collision detection
            // TO DO


            player[i].setPosition(playPos);

            if(shift)
                player[i].rotate();
            if(shoot && !bullet[i].getAct())
            {
                bullet[i].setPosition(player[i].getPos());
                Vec2 playerPos = player[i].getPos();
                Vec2 pointPos = Vec2(u, v);
                Vec2 playerToPointer = pointPos - playerPos;
                Vec2 angleVector = playerToPointer.normalize();
                bullet[i].setVelocity(angleVector*1000);
                bullet[i].setActive(true);
            }

        }


        for(int i=0; i<clientNumber; i++)
        {
            if(!bullet[i].getAct()) continue;
            Vec2 displacement = bullet[i].getVel()*dt;
            Vec2 pos = bullet[i].getPos()+displacement;
            bullet[i].setPosition(pos);
            bool hit = false;

            for(int j=0; j<clientNumber; j++)
            {
                if(bullet[i].getInd()==j) continue;

                Vec2 enemyPos = player[j].getPos();
                Vec2 resultant = enemyPos-pos;
                float distance = resultant.magnitude();
                Vec2 nearestToBullet = Vec2(clamp(pos.getX(), enemyPos.getX()-10, enemyPos.getY()+10), clamp(pos.getY(), enemyPos.getY()-20, enemyPos.getY()+20));
                Vec2 resultant2 = nearestToBullet-enemyPos;
                float enemyRad = resultant2.magnitude();

                if(distance<enemyRad+10)
                {
                    // HIT
                    hit = true;
                }
            }


            if(!hit)
            {
                float x = pos.getX();
                float y = pos.getY();
                int indX = floor(x/40);
                int indY = floor(y/40);

                if(indX-1>=0 && level.getPixel(indX-1, indY)==sf::Color::Black)
                {
                    float barX = ((indX-1)*40) + 20;
                    if(x-barX< 30)
                        hit = true;
                } else if(indX+1<40 && level.getPixel(indX+1, indY)==sf::Color::Black)  {
                    float barX = ((indX+1)*40) + 20;
                    if(barX-x< 30)
                        hit = true;
                } else if(indY-1>=0 && level.getPixel(indX, indY-1)==sf::Color::Black) {
                    float barY = ((indY-1)*40) + 20;
                    if(y-barY< 30)
                        hit = true;
                } else if(indY+1<21 && level.getPixel(indX, indY+1)==sf::Color::Black) {
                    float barY = ((indY-1)*4) + 20;
                    if(barY-y< 30)
                        hit = true;
                }
            }

            if(hit)
            {
                bullet[i].setPosition(-500, -500);
                bullet[i].setActive(false);
                bullet[i].setVelocity(Vec2(0, 0));
            }
        }


        sf::Packet sendPacket;
        for(int i=0; i<clientNumber; i++)
        {
            //std::c << player[i].getAcc().getX() << " " << player[i].getAcc().getY() << " -> " << player[i].getAcc().getDegree() << std::endl;
            sendPacket << player[i].getPos().getX() << player[i].getPos().getY() << (player[i].getAcc().getDegree()-90);
            sendPacket << bullet[i].getPos().getY() << bullet[i].getPos().getY();
        }

        for(int i=0; i<clientNumber; i++)
        {
            clients[i].send(sendPacket);
        }

    }

}

void GameServer::setGameState(GameState* state)
{
    gs = state;
}
