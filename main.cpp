#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <cmath>

#include "Boid.h"
#include "Renderer.h"
#include "FlockSystem.h"

#include "config.h"

Renderer screen("Honors: Experimentation", SCREEN_WIDTH, SCREEN_HEIGHT);

SDL_Texture* backdropTexture = IMG_LoadTexture(screen.getRenderer(), "./assets/backdrop.png"); 
SDL_Texture* boidTexture = screen.loadTexture("./assets/boid.png");

FlockSystem simulation;

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

const double FRAME_RATE = 1000 / 60.0;
const int BOIDS_TO_GENERATE = 250;

int mouseX, mouseY = 0;

void createBoid(int x, int y) {
    Boid boid = Boid(boidTexture, x, y, (rand() % 50 - 25) * 0.10, (rand() % 50 - 25) * 0.10, 24);
    simulation.add(boid);
}

int main(int argc, char** argv){

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    bool running = true;
    double before = 0;

    for (int i = 0; i < BOIDS_TO_GENERATE; i++) {
        createBoid(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
    }

    while(running) {

        double after = SDL_GetTicks();
        double delta = after - before;

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    // close on escape
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = false; 
                        std::cout << "Exiting via escape";
                    if (event.key.keysym.sym == SDLK_s)
                        createBoid(mouseX, mouseY);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    createBoid(mouseX, mouseY);
                    break;

                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    break;

                default:
                    break;
            }
        }

        if (delta > FRAME_RATE) {
            before = after;

            simulation.tick();
            std::vector<Boid> boids = simulation.getBoids();

            SDL_RenderCopy(screen.getRenderer(), backdropTexture, NULL, NULL); 

            for (Boid& boid : boids) {
                screen.render(boid);
            }

            SDL_RenderPresent(screen.getRenderer());
        }
    }

    return 0;
}