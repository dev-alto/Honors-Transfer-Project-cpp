#include "AABB.h"

AABB::AABB(Vec2 position, int width, int height) {
    this->lowerX = position.x;
    this->upperX = position.x + width;
    this->lowerY = position.y;
    this->upperY = position.y + height;

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