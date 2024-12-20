#include <vector>

#include "Vector.h"
#include "Boid.h"

class FlockSystem {
    public:
        FlockSystem() = default;

        void tick();
        void add(Boid &boid);
        Vec2 computeAlignment(Boid& thisBoid);
        Vec2 computeCohesion(Boid& thisBoid);
        Vec2 computeSeparation(Boid& thisBoid);

        std::vector<Boid> getBoids() {
            return boids;
        }

    private:
        int count;
        std::vector<Boid> boids;
};