#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include "State.h"
#include <string>
#include "GameServer.h"
#include "Renderer.h"

class GameState: public State
{
private:
    bool pressA;
    bool pressS;
    bool pressLShift;
    bool pressSpace;
    bool mousePressed;
    int players;
    int index;
    GameServer gs;
    bool isHost;
    bool isReady;
    sf::Font font;
    sf::TcpSocket client;
    sf::IpAddress ip;
    sf::Thread game_thread;
    Renderer renderer;

public:
    GameState();
    void gameReady();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
    void pass(std::string);
    void onDeactivate();
    void onKeyReleased(sf::Event);
    GameServer* getServer();
};

#endif // GAMESTATE_H_INCLUDED
