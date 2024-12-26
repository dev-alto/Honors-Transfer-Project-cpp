#include "Vector.h"
#include "AABB.h"

AABB::AABB(int x, int y, int width, int height) {
    this->lowerX = x;
    this->upperX = x + width;
    this->lowerY = y;
    this->upperY = y + height;

    this->width = width;
    this->height = height;
}

bool AABB::contains(Vec2 position) {
    return (
        lowerX <= position.x 
        && lowerY <= position.y 
        && position.x < upperX
        && position.y < upperY
    );
}

bool AABB::intersects(AABB &other) {
    return (
        upperX <= other.getLowerX()
        && upperY <= other.getLowerY()
        && other.getUpperX() < lowerX
        && other.getUpperY() < lowerY
    );
}