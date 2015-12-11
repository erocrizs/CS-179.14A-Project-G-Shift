#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Vec2.h"

class Bullet {
    Vec2 vel;
    Vec2 position;
    int playerId;
    float speedPerSecond;
    bool active;
    float rad;
public:
    Bullet(): speedPerSecond(300), active(false), rad(10) {};
    void update(float dt);
    void setCoords(Vec2);
    void setId(int i);
    void setVelocity(float, float);
    void activate(bool);
    bool isActive(){ return active;};
};

#endif // BULLET_H_INCLUDED
