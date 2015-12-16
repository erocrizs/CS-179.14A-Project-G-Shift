#ifndef GAMESERVER_H_INCLUDED
#define GAMESERVER_H_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "PlayerInfo.h"
#include "BulletInfo.h"

class GameState;
class GameServer {
private:
    int clientNumber;
    int joinedNumber;
    bool timesUp;
    bool running;
    GameState* gs;
    PlayerInfo player[4];
    BulletInfo bullet[4];
    sf::TcpSocket clients[4];
    sf::TcpListener listener;
    sf::Image level;
public:
    GameServer();
    void reset();
    void start_server();
    void setClientNumber(int);
    void timeFinish();
    void setGameState(GameState*);
};

#endif // GAMESERVER_H_INCLUDED
