#ifndef GAMESERVER_H_INCLUDED
#define GAMESERVER_H_INCLUDED

#include <SFML/Network.hpp>
class GameServer {
private:
    int clientNumber;
    int joinedNumber;
    bool timesUp;
    sf::TcpSocket clients[4];
public:
    GameServer();
    void reset();
    void start_server();
    void setClientNumber(int);
    void timeFinish();
};

#endif // GAMESERVER_H_INCLUDED
