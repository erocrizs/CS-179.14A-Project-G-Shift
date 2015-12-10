#ifndef JOINSTATE_H_INCLUDED
#define JOINSTATE_H_INCLUDED
#include "Button.h"
#include "State.h"

class JoinState: public State
{
private:
    Button back, forth;
    sf::Font font;
public:
    JoinState();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onClick(float, float);
    void getText(std::string text);
    void accept();
};


#endif // JOINSTATE_H_INCLUDED
