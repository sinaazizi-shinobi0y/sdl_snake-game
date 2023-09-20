#include <iostream>
#include <SDL.h>
#include "./jj.h"
#include <vector>

using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "error initializing sdl ... \n");
        return false;
    }
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("shinobi____", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, NULL);
    return true;
}

int main(int argc, char* args[]) {
    int dir = 0;
    enum direction {
        down,
        left,
        right,
        up,
    };
    int fx = 360;
    int fy = 300;
    initialize_window();
    SDL_Event e;
    bool grun = true;
    SDL_Rect head{ 400,400,20,20 };
    vector<SDL_Rect> tail;
    int tailLength = 0; 

    while (grun) {
        SDL_Rect food{ fx,fy,20,20 };
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { grun = false; }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_DOWN) { dir = down; }
                if (e.key.keysym.sym == SDLK_LEFT) { dir = left; }
                if (e.key.keysym.sym == SDLK_UP) { dir = up; }
                if (e.key.keysym.sym == SDLK_RIGHT) { dir = right; }
            }
        }
        SDL_Rect leftwall{ 0,0,10,1600 };
        SDL_Rect rightwall{ 790,0,10,1600 };
        SDL_Rect upperwall{ 0,0,800,10 };
        SDL_Rect downwall{ 0,790,800,10 };
        if (head.x > 790 || head.x < 10 || head.y < 10 || head.y>790) {
            tail.clear();
            tailLength = 0;
            head.x = 400;
            head.y = 400;
        }
        switch (dir) {
        case down:head.y += 5; break;
        case up:head.y -= 5; break;
        case left:head.x -= 5; break;
        case right:head.x += 5; break;
        }
        for (auto& t : tail){
        if (head.x == t.x && head.y == t.y) {
            tail.clear();
            tailLength = 0;
        }
    }

        tail.push_back({ head.x, head.y, 20, 20 });

        
        if (tail.size() > tailLength) {
            tail.erase(tail.begin());
        }

        // Check for collision with food
        if (head.x >= fx - 10 && head.x <= fx + 10 && head.y >= fy - 10 && head.y <= fy + 10) {
            fx = rand() % 80 * 10;
            fy = rand() % 80 * 10;
            tailLength+=5; // Increase the tail length when food is eaten
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &head);
        for (auto& t : tail) {
            SDL_RenderFillRect(renderer, &t);
        }

        SDL_SetRenderDrawColor(renderer, 72, 161, 146, 255);
        SDL_RenderFillRect(renderer, &leftwall);
        SDL_RenderFillRect(renderer, &rightwall);
        SDL_RenderFillRect(renderer, &upperwall);
        SDL_RenderFillRect(renderer, &downwall);
        SDL_SetRenderDrawColor(renderer, 26, 204, 114, 255);
        SDL_RenderFillRect(renderer, &food);

        SDL_RenderPresent(renderer);

        SDL_Delay(25);
    }

    return 0;
}
