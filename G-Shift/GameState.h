#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include "Button.h"
#include "State.h"
#include <string>
#include "GameServer.h"
#include "Block.h"

class GameState: public State
{
private:
    GameServer gs;
    bool isHost;
    bool isReady;
    int player;
    sf::Font font;
    sf::TcpSocket client;
    sf::IpAddress ip;
    sf::Thread game_thread;
    sf::Image levelFile;
    Block blockList[40][21];
public:
    GameState();
    void gameReady();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
    void pass(std::string);
    void onDeactivate();
    GameServer* getServer();
};

#endif // GAMESTATE_H_INCLUDED
