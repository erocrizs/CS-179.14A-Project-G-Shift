#include "Player.h"

Player::Player()
{
    orientation = 0;
    position = Vec2(0, 0);
    jumpTime = 0;
}

void Player::setOrientation(int i)
{
    orientation = i;
}

void Player::setPosition(float x, float y)
{
    position = Vec2(x, y);
}

Vec2 Player::getPosition()
{
    return position;
}

int Player::getOrientation()
{
    return orientation;
}

void Player::jumpUp(float dt)
{
    float disp = position.getY();
    jumpTime += dt;
    if(jumpTime >= 0.5){
        jump = false;
        disp -= (jumpTime-0.5)*80;
    }else{
        disp += (dt*80);
    }
    switch(orientation)
    {
    case 1:
        setPosition(position.getX(), position.getY()-disp);
        break;
    case 2:
        setPosition(position.getX()-disp, position.getY());
        break;
    case 3:
        setPosition(position.getX(), position.getY()+disp);
        break;
    case 4:
        setPosition(position.getX()+disp, position.getY());
        break;
    }
}

void Player::move(int dir, float dt)
{
    float disp = dir*dt*160;

        switch(orientation)
        {
        case 1:
            setPosition(position.getX()+disp, position.getY());
            break;
        case 2:
            setPosition(position.getX(), position.getY()-disp);
            break;
        case 3:
            setPosition(position.getX()-disp, position.getY());
            break;
        case 4:
            setPosition(position.getX(), position.getY()+disp);
            break;
        }

}

void Player::fall(float dt)
{
    float disp = (dt*80);
    switch(orientation)
    {
    case 1:
        setPosition(position.getX(), position.getY()+disp);
        break;
    case 2:
        setPosition(position.getX()+disp, position.getY());
        break;
    case 3:
        setPosition(position.getX(), position.getY()-disp);
        break;
    case 4:
        setPosition(position.getX()-disp, position.getY());
        break;
    }
}
