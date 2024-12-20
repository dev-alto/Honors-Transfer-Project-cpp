#include "Vector.h"

double Vec2::length(){
    return sqrt(pow(x, 2) + pow(y, 2));
};

void Vec2::normalise(){
    double length = this->length(); 
    if (length != 0) {
        x /= length;
        y /= length;
    };
};

Vec2 Vec2::normalised(){
    double length = this->length();
    if (length == 0){
        return Vec2(1, 0);
    } else {
        return Vec2(x/length, y/length);
    };
};

void Vec2::limit(double limit){
    if (length() > limit){
        normalise();
        x *= limit;
        y *= limit;
    }
};

Vec2 Vec2::operator+(Vec2 other){
    return Vec2(x + other.x, y + other.y);
};

Vec2 Vec2::operator-(Vec2 other){
    return Vec2(x - other.x, y - other.y);
};

void Vec2::operator+=(Vec2 other){
    x += other.x;
    y += other.y;
};

void Vec2::operator-=(Vec2 other){
    x -= other.x;
    y -= other.y;
};

Vec2 Vec2::operator*(double other){
    return Vec2(x * other, y * other);
};

Vec2 Vec2::operator/(double other){
    return Vec2(x / other, y / other);
};

void Vec2::operator*=(double other){
    x *= other;
    y *= other;
};

void Vec2::operator/=(double other){
    x /= other;
    y /= other;
};

double Vec2::dot(Vec2 other){
    return (x * other.x + y * other.y);
};