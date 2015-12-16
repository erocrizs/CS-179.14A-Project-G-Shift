#include "GameServer.h"
#include <iostream>
#include <math.h>
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

    player[0].setPosition(Vec2(60, 60));

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

            if(endX==initX && initY!=endY)
            {
                int prev = -1;
                int offset = 20;//initY<endY ? 30 : 10 ;
                for(int i=initY; ; )
                {
                    if((initY<endY && i>endY)||(initY>endY && i<endY)) break;

                    if(level.getPixel(initX, i)==sf::Color::Black)
                    {
                        playPos = Vec2(playPos.getX(), (prev*40)+offset);
                        endX = floor(playPos.getX()/40.0);
                        endY = floor(playPos.getY()/40.0);
                        break;
                    }
                    if( playPos.getX()<((initX*40)+10) && level.getPixel(initX-1, i)==sf::Color::Black)
                    {
                        playPos = Vec2(playPos.getX(), (prev*40)+offset);
                        endX = floor(playPos.getX()/40.0);
                        endY = floor(playPos.getY()/40.0);
                        break;
                    }
                    if( playPos.getX()>((initX*40)+30) && level.getPixel(initX+1, i)==sf::Color::Black)
                    {
                        playPos = Vec2(playPos.getX(), (prev*40)+offset);
                        endX = floor(playPos.getX()/40.0);
                        endY = floor(playPos.getY()/40.0);
                        break;
                    }
                    prev = i;
                    if(initY<endY) i++;
                    else if(initY>endY) i--;
                }
            }
            else if(endY==endY && initX!=endX)
            {
                int prev = -1;
                int offset = 20;//initX<endX ? 30 : 10 ;
                for(int i=initX; ; )
                {
                    if((initX<endX && i>endX)||(initX>endX && i<endX)) break;

                    if(level.getPixel(i, initY)==sf::Color::Black)
                    {
                        playPos = Vec2((prev*40)+offset, playPos.getY());
                        endX = floor(playPos.getX()/40.0);
                        endY = floor(playPos.getY()/40.0);
                        break;
                    }
                    if( playPos.getY()<((initY*40)+10) && level.getPixel(i, initY-1)==sf::Color::Black)
                    {
                        playPos = Vec2((prev*40)+offset, playPos.getY());
                        endX = floor(playPos.getX()/40.0);
                        endY = floor(playPos.getY()/40.0);
                        break;
                    }
                    if( playPos.getY()>((initY*40)+30) && level.getPixel(i, initY+1)==sf::Color::Black)
                    {
                        playPos = Vec2((prev*40)+offset, playPos.getY());
                        endX = floor(playPos.getX()/40.0);
                        endY = floor(playPos.getY()/40.0);
                        break;
                    }

                    prev = i;
                    if(initX<endX) i++;
                    else if(initX>endX) i--;
                }

            }
            else if(endX==initX && endY==initY)
            {
                for(int i=-1; i<=1; i+=2)
                {
                    for(int j=-1; j<=1; j+=2)
                    {
                        if(clamp(initX+i, 0, 40)!=initX+j || clamp(initY+j, 0, 21)!=initY+j) continue;
                        if(i!=0 && level.getPixel(initX+i, initY)==sf::Color::Black)
                        {
                            float blockX = (initX+i)*40+20;
                            float blockY = initY*40+20;
                            Vec2 block(blockX, blockY);
                            Vec2 resultant = block-playPos;

                            Vec2 nearestFromBlock(clamp(playPos.getX(), blockX-20, blockX+20), clamp(playPos.getY(), blockY-20, blockY+20));
                            Vec2 nearestFromPlayer(clamp(blockX, playPos.getX()-20, playPos.getX()+20), clamp(blockY, playPos.getY()-20, playPos.getY()+20));
                            Vec2 blockCenterToNearest = nearestFromBlock-block;
                            Vec2 playerCenterToNearest = nearestFromPlayer-playPos;

                            float distBetweenCenters = resultant.magnitude();
                            float a = blockCenterToNearest.magnitude();
                            float b = playerCenterToNearest.magnitude();
                            if(distBetweenCenters+3 < a + b) //collide
                            {
                                playPos = Vec2(initX*40+20, playPos.getY());
                                std::cout << "a" << std::endl;
                            }
                        }
                        if(j!=0 && level.getPixel(initX, initY+j)==sf::Color::Black)
                        {
                            float blockX = initX*40+20;
                            float blockY = (initY+j)*40+20;
                            Vec2 block(blockX, blockY);
                            Vec2 resultant = block-playPos;

                            Vec2 nearestFromBlock(clamp(playPos.getX(), blockX-20, blockX+20), clamp(playPos.getY(), blockY-20, blockY+20));
                            Vec2 nearestFromPlayer(clamp(blockX, playPos.getX()-20, playPos.getX()+20), clamp(blockY, playPos.getY()-20, playPos.getY()+20));
                            Vec2 blockCenterToNearest = nearestFromBlock-block;
                            Vec2 playerCenterToNearest = nearestFromPlayer-playPos;

                            float distBetweenCenters = resultant.magnitude();
                            float a = blockCenterToNearest.magnitude();
                            float b = playerCenterToNearest.magnitude();
                            if(distBetweenCenters+3 < a + b) //collide
                            {
                                playPos = Vec2(playPos.getX(), initY*40+20);
                                std::cout << "b" << std::endl;
                            }

                        }
                    }
                }
            }

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
            std::cout << player[i].getAcc().getX() << " " << player[i].getAcc().getY() << " -> " << player[i].getAcc().getDegree() << std::endl;
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
