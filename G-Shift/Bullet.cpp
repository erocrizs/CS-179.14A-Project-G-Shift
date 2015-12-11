#include "Bullet.h"

void Bullet::update(float dt)
{
    position = position + (vel*dt);
}

void Bullet::setCoords(Vec2 newpos)
{
    position = newpos;
}

void Bullet::setId(int id)
{
    playerId = 0;
}

void Bullet::setVelocity(float x, float y)
{
    Vec2 temp = Vec2(x, y);
    temp = temp.normalize();
    vel = temp*speedPerSecond;
}

void Bullet::activate(bool p)
{
    active = p;
}
