#ifndef PLAYERINFO_H_INCLUDED
#define PLAYERINFO_H_INCLUDED
#include "Vec2.h"

class PlayerInfo
{
private:
    Vec2 horizontalVelocity;
    Vec2 fallVelocity;
    Vec2 acceleration;
    Vec2 position;
public:
    PlayerInfo() {
        fallVelocity = Vec2(0, 0);
        acceleration = Vec2(0, 1000);
        horizontalVelocity = Vec2(200, 0);
    }
    Vec2 getPos() {return position;}
    Vec2 getAcc() {return acceleration;}
    Vec2 getFallVel() {return fallVelocity;}
    Vec2 getHorizontalVel() {return horizontalVelocity;}
    void setAcceleration(Vec2 acc) {
        acceleration = acc;
    }
    void setPosition(Vec2 pos) {
        position = pos;
    }
    void setFallVelocity(Vec2 vel) {
        fallVelocity = vel;
    }
    void rotate() {
        horizontalVelocity = horizontalVelocity.perpCCW();
        fallVelocity = fallVelocity.perpCCW();
        acceleration = acceleration.perpCCW();
    }
};

#endif // PLAYERINFO_H_INCLUDED
