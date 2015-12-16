#ifndef BULLETINFO_H_INCLUDED
#define BULLETINFO_H_INCLUDED

#include "Vec2.h"
class BulletInfo{
private:
    int index;
    Vec2 velocity;
    Vec2 position;
    bool active;
public:
    BulletInfo() {
        index = 0;
        velocity = Vec2(0, 0);
        position = Vec2(-500, -500);
        active = false;
    }
    bool getAct() {return active;}
    int getInd() {return index;}
    Vec2 getPos() {return position;}
    Vec2 getVel() {return velocity;}
    void setIndex(int ind) {
        index = ind;
    }
    void setPosition(Vec2 pos) {
        position = pos;
    }
    void setPosition(float a, float b) {
        position = Vec2(a, b);
    }
    void setVelocity(Vec2 vel) {
        velocity = vel;
    }
    void setActive(bool act) {
        active = act;
    }
};

#endif // BULLETINFO_H_INCLUDED
