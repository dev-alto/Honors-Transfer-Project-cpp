#include <map>

#include <AABB.h>
#include <Vector.h>

template <typename T>
class Quadtree {
    public:
        Quadtree(Vec2 position, int width, int height, int maxRecursions, int splitThreshold);
        Quadtree(Vec2 position, int width, int height, Quadtree &parent);
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

        Quadtree<T> parent;
        Quadtree<T> subTrees[4];
        std::map<std::T, Vec2> contents;
};