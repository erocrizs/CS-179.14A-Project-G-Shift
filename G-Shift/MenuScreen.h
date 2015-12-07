#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

#include "Button.h"

class MenuScreen: public State
{
private:
    Vec2 position;
    Vec2 half_diagonal;
public:
    Splash();
    void update(float);
    void draw(sf::RenderWindow&);
    void onActivate();
    void onDeactivate();
};

#endif // MENUSCREEN_H_INCLUDED
