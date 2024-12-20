#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <math.h>

class Boid {
    public:
        Boid() = default;
        Boid(SDL_Texture* texture, double initX, double initY, double initVelX, double initVelY, int size);

        double getX() {
            return x;
        }
        void setX(double x) {
            this->x = x;
        }
        double getY() {
            return y;
        }
        void setY(double y) {
            this->y = y;
        }
        double getVelX() {
            return velX;
        }
        void setVelX(double velX) {
            this->velX = velX;
        }
        double getVelY() {
            return velY;
        }
        void setVelY(double velY) {
            this->velY = velY;
        }
        int getHalfSize() {
            return halfSize;
        }
        int getSize() {
            return size;
        }
        double getAngle() {
            return angle;
        }
        void setAngle(double angle) {
            this->angle = angle;
        }
        int getId() {
            return id;
        }
        int getNeighbors() {
            return neighbors;
        }
        void setNeighbors(int neighbors) {
            this->neighbors = neighbors;
        }
        int getRange() {
            return range;
        }
        int getSquaredRange() {
            return squaredRange;
        }

        SDL_Texture* getTexture() {
            return texture;
        }
        std::string getMetaText() {
            return metaText;
        }
        void setMetaText(std::string meta) {
            this->metaText = meta;
        }

        void tick(double deltaTime);
        double distanceToSquared(Boid& other);
        double distanceToSquared(double x, double y);

    private:
        int id;
        double x, y;
        double velX, velY;
        double angle;

        int size, halfSize;
        int range = 32;
        int squaredRange = pow(range, 2);

        int neighbors = 0;

        std::string metaText = "";
        SDL_Texture* texture;
};