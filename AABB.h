#pragma once

#include "Vector.h"

class AABB {
    public: 
        AABB() = default;
        AABB(int x, int y, int width, int height);
        int getLowerX() {
            return lowerX;
        }
        int getLowerY() {
            return lowerY;
        }
        int getUpperX() {
            return upperX;
        }
        int getUpperY() {
            return upperY;
        }
        int getWidth() {
            return width;
        }
        int getHeight() {
            return height;
        }

        bool contains(Vec2 position);
        bool intersects(AABB &other);

    private:
        int width, height;
        int lowerX, upperX;
        int lowerY, upperY;
};