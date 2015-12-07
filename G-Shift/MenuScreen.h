#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

class MenuScreen: public State
{
private:
    bool isFadingIn;
    bool isOnPause;
    bool isFadingOut;
    float timeCount;
    int logoAlpha;
public:
    Splash();
    void update(float);
    void draw(sf::RenderWindow&);
    void onActivate();
};

#endif // MENUSCREEN_H_INCLUDED
