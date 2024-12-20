#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string> 
#include <iostream>

#include "Boid.h"
#include "Renderer.h"

int _ = TTF_Init();
const SDL_Color WHITE = {255, 255, 255};

TTF_Font* GoogleSans = TTF_OpenFont("./assets/GoogleSansDisplay-Bold.ttf", 16);

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

Renderer::Renderer(const char* title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* Renderer::loadTexture(const char* filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void Renderer::render(Boid& boid) {

    // need to adjust for top-left renders positioning 
    SDL_Rect boidRect;
    boidRect.x = boid.getX() - boid.getHalfSize();
    boidRect.y = boid.getY() - boid.getHalfSize();

    boidRect.h = boid.getSize();
    boidRect.w = boidRect.h;

    // SDL_Surface* messageSurface = TTF_RenderText_Solid(GoogleSans, boid.getMetaText().c_str(), WHITE); 
    // SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    // SDL_FreeSurface(messageSurface);

    // int messagePixelWidth = 0;
    // int messagePixelHeight = 0;

    // SDL_Rect messageRect;
    // TTF_SizeText(GoogleSans, boid.getMetaText().c_str(), &messageRect.w, &messageRect.h); // Size the texture so it renders the text correctly.

    // messageRect.x = boid.getX() - messageRect.w * 0.5;  //controls the rect's x coordinate 
    // messageRect.y = boid.getY() + boid.getHalfSize(); // controls the rect's y coordinte

    // SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
    // SDL_DestroyTexture(messageTexture);

    // DrawCircle(renderer, boid.getX(), boid.getY(), boid.getRange());
    SDL_RenderCopyEx(renderer, boid.getTexture(), NULL, &boidRect, boid.getAngle(), 0, SDL_FLIP_NONE);
}