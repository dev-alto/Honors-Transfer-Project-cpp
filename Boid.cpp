#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "Boid.h"
#include "config.h"

Boid::Boid(SDL_Texture* texture, double initX, double initY, double initVelX, double initVelY, int size) {
    this->x = initX;
    this->y = initY;

    this->velX = initVelX;
    this->velY = initVelY;

    this->size = size;
    this->halfSize = size / 2;
    this->texture = texture;
}

void Boid::tick(double deltaTime) {
    // bounce vel of boids off walls
    // if (x > SCREEN_WIDTH) {
    //     velX = -abs(velX) - 1;
    //     x = SCREEN_WIDTH;
    // } else if (x < 0) {
    //     velX = abs(velX) + 1;
    //     x = 0;
    // }
    // if (y > SCREEN_HEIGHT) {
    //     velY = -abs(velY) - 1;
    //     y = SCREEN_HEIGHT;
    // } else if (y < 0) {
    //     velY = abs(velY) + 1;
    //     y = 0;
    // }

    if (x > SCREEN_WIDTH) {
        x = 0;
    } else if (x < 0) {
        x = SCREEN_WIDTH;
    }
    if (y > SCREEN_HEIGHT) {
        y = 0;
    } else if (y < 0) {
        y = SCREEN_HEIGHT;
    }

    x += velX;
    y += velY;

    setAngle(atan2(velY, velX) * (180.0 / M_PI) + 90);
}

double Boid::distanceToSquared(Boid &other) {
    return pow(this->getX() - other.getX(), 2) + pow(this->getY() - other.getY(), 2);
}

double Boid::distanceToSquared(double x, double y) {
    return pow(this->getX() - x, 2) + pow(this->getY() - y, 2);
}