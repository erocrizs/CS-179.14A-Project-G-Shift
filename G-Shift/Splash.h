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
    int logoAlpha;
public:
    Splash();
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    void onActivate();
    void onDeactivate();
};

#endif // SPLASH_H_INCLUDED
