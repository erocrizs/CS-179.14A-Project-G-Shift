#ifndef SPLASH_H_INCLUDED
#define SPLASH_H_INCLUDED

#include "State.h"

class Splash: public State
{
private:
    bool isFadingIn;
    bool isOnPause;
    bool isFadingOut;
    float timeCount;
    unsigned int logoAlpha;
public:
    Splash();
    void update(float);
    void draw(sf::RenderWindow&);
    void onActivate();
};

#endif // SPLASH_H_INCLUDED
