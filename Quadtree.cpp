#include <AABB.h>
#include <Vector>
#include <iostream>

#include "Vector.h"
#include "Quadtree.h"

template <typename T>
Quadtree<T>::Quadtree(Vec2 position, int width, int height, int maxRecursions, int splitThreshold) {
    this->bounds = AABB(position, width, height);
    this->maxRecursions = maxRecursions;
    this->splitThreshold = splitThreshold;
    this->parent = NULL;
    layer = 0;
}

template <typename T>
Quadtree<T>::Quadtree(Vec2 position, int width, int height, Quadtree &parent) {
    this->bounds = AABB(position, width, height);
    this->maxRecursions = parent.maxRecursions;
    this->splitThreshold = parent.splitThreshold;
    this->parent = parent;
    layer = parent.layer + 1;
}

template <typename T>
void Quadtree<T>::insertPoint(Vec2 position, T &object) {

    if !(bounds.contains(position)) {
        std::cout << "not contained!" << endl;
        return;
    }

    if (size < splitThreshold || layer == maxRecursions) {
        size++;
        
        contents.insert(object, position);
    } else {
        if (!split) {
            subdivide();
        }

        for (int i = 0; i < 4; i++) {
            subTrees[i].insertPoint(position, object);
        }
    }
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

