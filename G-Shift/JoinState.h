#ifndef JOINSTATE_H_INCLUDED
#define JOINSTATE_H_INCLUDED
#include "Button.h"
#include "State.h"

class JoinState: public State
{
private:
    Button back;
    sf::Font font;
public:
    JoinState();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
};


#endif // JOINSTATE_H_INCLUDED
