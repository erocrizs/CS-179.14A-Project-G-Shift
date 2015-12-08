#ifndef JOINSTATE_H_INCLUDED
#define JOINSTATE_H_INCLUDED
#include "Button.h"
#include "State.h"

class GameState: public State
{
private:
    Button back;
    sf::Font font;
public:
    GameState();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
};


#endif // JOINSTATE_H_INCLUDED
