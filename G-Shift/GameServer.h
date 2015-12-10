#ifndef GAMESERVER_H_INCLUDED
#define GAMESERVER_H_INCLUDED

#include <SFML/Network.hpp>

class GameState;
class GameServer {
private:
    int clientNumber;
    int joinedNumber;
    bool timesUp;
    bool running;
    GameState* gs;
    sf::TcpSocket clients[4];
    sf::TcpListener listener;
public:
    GameServer();
    void reset();
    void start_server();
    void setClientNumber(int);
    void timeFinish();
    void setGameState(GameState*);
};

#endif // GAMESERVER_H_INCLUDED
