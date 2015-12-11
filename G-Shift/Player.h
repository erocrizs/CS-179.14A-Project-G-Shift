#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Vec2.h"

class Player {
private:
    float jumpTime;
    Vec2 position;
    int orientation;
    bool jump;
public:
    Player();
    void setPosition(float x, float y);
    Vec2 getPosition();
    void setOrientation(int);
    int getOrientation();
    bool isJumping(){return jump;};
    void jumpUp(float dt);
    void move(int dir, float dt);
    void fall(float dt);
};

#endif // PLAYER_H_INCLUDED
