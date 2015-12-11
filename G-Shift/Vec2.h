#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2
{
private:
    float x;
    float y;
public:
    float getX();
    float getY();

    Vec2();
    Vec2(float, float);
    Vec2 operator+ (Vec2);
    Vec2 operator- (Vec2);
    Vec2 operator* (float);
    float operator* (Vec2);
    float operator% (Vec2);
    float magnitude();
    Vec2 normalize();
    Vec2 perp();
};

float clamp(float, float, float);

#endif // VEC2_H_INCLUDED
