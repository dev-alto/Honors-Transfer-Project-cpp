#include <SDL2/SDL.h>
#include <vector>
#include <math.h>

#include "Vector.h"
#include "Boid.h"
#include "FlockSystem.h"

double getSquaredMagnitude(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void FlockSystem::add(Boid &boid) {
    boids.push_back(boid);
}

void FlockSystem::tick() {
    for (Boid& thisBoid : boids) {
        Vec2 alignment = computeAlignment(thisBoid) * 1.1;
        Vec2 cohesion = computeCohesion(thisBoid) * 1.05;
        Vec2 separation = computeSeparation(thisBoid) * 1.1;
        
        Vec2 globalGravity;
        globalGravity.x = 0;
        globalGravity.y = 0;

        Vec2 limitedVector(
            thisBoid.getVelX() + alignment.x + cohesion.x + separation.x, 
            thisBoid.getVelY() + alignment.y + cohesion.y + separation.y + globalGravity.y
        );
        
        limitedVector.limit(3);
        thisBoid.setVelX(limitedVector.x);
        thisBoid.setVelY(limitedVector.y);
        thisBoid.tick(1);
    }
}

Vec2 FlockSystem::computeAlignment(Boid& thisBoid) {

    double velX = 0;
    double velY = 0;

    double neighbors = 0;

    for (Boid& otherBoid : boids) {
        if (&thisBoid != &otherBoid) {
            if (thisBoid.distanceToSquared(otherBoid) < thisBoid.getSquaredRange()) {
                velX += otherBoid.getVelX();
                velY += otherBoid.getVelY();
                neighbors++;
            }
        }
    }

    if (neighbors > 0) {
        velX /= neighbors;
        velY /= neighbors;
        double magnitude = getSquaredMagnitude(velX, velY);
        velX /= magnitude;
        velY /= magnitude;
    }

    Vec2 vel;
    vel.x = velX;
    vel.y = velY;

    std::string str = std::to_string (neighbors);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    thisBoid.setMetaText(str);

    return vel; 
}

Vec2 FlockSystem::computeCohesion(Boid& thisBoid) {

    double centralX = 0;
    double centralY = 0;

    double neighbors = 0;

    for (Boid& otherBoid : boids) {
        if (&thisBoid != &otherBoid) {
            if (thisBoid.distanceToSquared(otherBoid) < thisBoid.getSquaredRange()) {
                centralX += otherBoid.getX();
                centralY += otherBoid.getY();
                neighbors++;
            }
        }
    }

    Vec2 vel;
    vel.x = 0;
    vel.y = 0;

    if (neighbors > 0) {
        centralX /= neighbors;
        centralY /= neighbors;
        vel.x = (centralX - thisBoid.getX());
        vel.y = (centralY - thisBoid.getY());
        vel.normalise();
    }
    

    return vel; 
}

Vec2 FlockSystem::computeSeparation(Boid& thisBoid) {

    double steerX = 0;
    double steerY = 0;

    double neighbors = 0;

    for (Boid& otherBoid : boids) {
        if (&thisBoid != &otherBoid) {
            if (thisBoid.distanceToSquared(otherBoid) < thisBoid.getSquaredRange()) {
                steerX += otherBoid.getX() - thisBoid.getX();
                steerY += otherBoid.getY() - thisBoid.getY();
                neighbors++;
            }
        }
    }

    if (neighbors > 0) {
        steerX /= neighbors;
        steerY /= neighbors;
    }

    Vec2 vel;
    vel.x = -(steerX);
    vel.y = -(steerY);
    vel.normalise();

    return vel; 
}