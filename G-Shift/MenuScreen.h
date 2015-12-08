#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"

class MenuScreen: public State
{
private:
    Button host;
    Button join;
	sf::Texture logoTexture;
	int cover;
public:
    MenuScreen();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
};

#endif // MENUSCREEN_H_INCLUDED
