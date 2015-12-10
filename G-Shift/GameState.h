#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include "Button.h"
#include "State.h"
#include <string>

class GameState: public State
{
private:
    Button back;
    sf::Font font;
public:
    GameState();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
    void onActivate();
    void pass(std::string);
};

#endif // GAMESTATE_H_INCLUDED
