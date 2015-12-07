#include "Vec2.h"
#include <cmath>
#include <algorithm>

Vec2::Vec2(float a, float b)
{
    x = a;
    y = b;
}

float Vec2::getX()
{
    return x;
}

float Vec2::getY()
{
    return y;
}

Vec2 Vec2::operator+(Vec2& that)
{
    Vec2 ret(x+that.getX(), y+that.getY());
    return ret;
}

Vec2 Vec2::operator-(Vec2& that)
{
    Vec2 ret(x-that.getX(), y-that.getY());
    return ret;
}

Vec2 Vec2::operator*(float i)
{
    Vec2 ret(x*i, y*i);
    return ret;
}

float Vec2::operator*(Vec2& that)
{
    return (x*that.getX()) + (y*that.getY());
}

float Vec2::operator%(Vec2& that)
{
    return (x*that.getY())-(y*that.getX());
}

float Vec2::magnitude()
{
    return std::sqrt((x*x)+(y*y));
}

Vec2 Vec2::normalize()
{
    float mag = this->magnitude();
    Vec2 ret(x/mag, y/mag);
    return ret;
}

Vec2 Vec2::perp()
{
    Vec2 ret(-y, x);
    return ret;
}

float clamp(float val, float bot, float top)
{
    return std::min(top, std::max(val, bot));
}
