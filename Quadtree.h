#pragma once

#include <map>

#include "AABB.h"
#include "Vector.h"

template <typename T>
class Quadtree {
    public:
        Quadtree() = default;
        Quadtree(int x, int y, int width, int height, int maxRecursions, int splitThreshold);
        Quadtree(int x, int y, int width, int height, Quadtree &parent);
        void insertPoint(Vec2 position, T &object);
        void updatePoint(Vec2 position, T &object);
        void deletePoint(T object);
        int getSize();
        void subdivide();
        void render();
    private:
        AABB bounds;

        int maxRecursions;
        int splitThreshold;

        int layer;
        int size;
        bool split = false;

        Quadtree<T>* parent;
        Quadtree<T>* subTrees[4];
        std::map<T, Vec2> contents;
};

template <typename T>
Quadtree<T>::Quadtree(int x, int y, int width, int height, int maxRecursions, int splitThreshold) {
    this->bounds = AABB(x, y, width, height);
    this->maxRecursions = maxRecursions;
    this->splitThreshold = splitThreshold;
    this->parent = NULL;
    layer = 0;
}

template <typename T>
Quadtree<T>::Quadtree(int x, int y, int width, int height, Quadtree &parent) {
    this->bounds = AABB(x, y, width, height);
    this->maxRecursions = parent.maxRecursions;
    this->splitThreshold = parent.splitThreshold;
    this->parent = parent;
    layer = parent.layer + 1;
}

template <typename T>
void Quadtree<T>::insertPoint(Vec2 position, T &object) {

    if (!bounds.contains(position)) {
        std::cout << "not contained!" << std::endl;
        return;
    }

    // if (size < splitThreshold || layer == maxRecursions) {
    //     size++;
        
    //     contents.insert(object, position);
    // } else {
    //     if (!split) {
    //         subdivide();
    //     }

    //     for (int i = 0; i < 4; i++) {
    //         subTrees[i].insertPoint(position, object);
    //     }
    // }
}

template <typename T>
void Quadtree<T>::subdivide() {
    int halfWidth = bounds.getWidth() / 2;
    int halfHeight = bounds.getHeight() / 2;

    Quadtree<T> TL = Quadtree(bounds.getLowerX(), bounds.getLowerY(), halfWidth, halfHeight);
    Quadtree<T> TR = Quadtree(bounds.getLowerX() + halfWidth, bounds.getLowerY(), halfWidth, halfHeight);
    Quadtree<T> BL = Quadtree(bounds.getLowerX(), bounds.getLowerY() + halfHeight, halfWidth, halfHeight);
    Quadtree<T> BR = Quadtree(bounds.getLowerX() + halfWidth, bounds.getLowerY() + halfHeight, halfWidth, halfHeight);
    subTrees[0] = TL;
    subTrees[1] = TR;
    subTrees[2] = BL;
    subTrees[3] = BR;

    split = true;
}

