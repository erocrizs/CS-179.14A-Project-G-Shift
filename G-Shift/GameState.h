#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include "Button.h"
#include "State.h"
#include <string>
#include "GameServer.h"

class GameState: public State
{
private:
    GameServer gs;
    bool isHost;
    Button back;
    sf::Font font;
    sf::Text taking;
    sf::TcpSocket client;
    sf::IpAddress ip;
    sf::Thread game_thread;
public:
    GameState();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
    void pass(std::string);
    GameServer* getServer();
};

#endif // GAMESTATE_H_INCLUDED
