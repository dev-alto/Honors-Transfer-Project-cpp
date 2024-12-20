#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Boid.h"

class Renderer {
    public:
        Renderer(const char* title, int width, int height);
        
        SDL_Texture* loadTexture(const char* filePath);

        SDL_Renderer* getRenderer() {
            return renderer;
        }

        void render(Boid& boid);

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};