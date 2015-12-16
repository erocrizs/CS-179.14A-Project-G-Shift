#ifndef HOSTSTATE_H_INCLUDED
#define HOSTSTATE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"

class HostState: public State
{
private:
    Button back;
    Button practice;
    Button twoPlayer;
    Button threePlayer;
    Button fourPlayer;
    sf::Font font;
public:
    HostState();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
};

#endif // HOSTSTATE_H_INCLUDED
