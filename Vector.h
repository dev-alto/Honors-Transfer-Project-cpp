#ifndef VECTOR2
#define VECTOR2

#include <math.h>

struct Vec2
{
    double x;
    double y;
    Vec2(double _x, double _y): x(_x), y(_y) {};
    Vec2(): x(0), y(0) {};
    double length();
    Vec2 normalised();
    void normalise();
    void limit(double);
    
    Vec2 operator+(Vec2);
    Vec2 operator-(Vec2);

    void operator+=(Vec2);
    void operator-=(Vec2);

    Vec2 operator*(double);
    Vec2 operator/(double);

    void operator*=(double);
    void operator/=(double);
    
    double dot(Vec2);

};

#endif