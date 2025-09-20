#include "VVGA.h"
#include "verilated.h"
#include <SDL2/SDL.h>
#include <iostream>

#define WIDTH 800   
#define HEIGHT 600

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VVGA* top = new VVGA;

    // SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("VGA Output", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Reset phase
    top->reset = 1;
    for (int i = 0; i < 10; ++i) {
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();
    }
    top->reset = 0;

    // Main simulation loop
    for (int i = 0; i < 1000000; ++i) {
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();

        // Access internal signals
        bool video_on = top->VGA__DOT__video_on;
        uint32_t hcount = top->VGA__DOT__hcount;
        uint32_t vcount = top->VGA__DOT__vcount;

        if (video_on && hcount < WIDTH && vcount < HEIGHT) {
            uint8_t r = top->red << 4;
            uint8_t g = top->green << 4;
            uint8_t b = top->blue << 4;

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawPoint(renderer, hcount, vcount);
        }

        // Update display 
        if (i % (WIDTH * HEIGHT) == 0) {
            SDL_RenderPresent(renderer);
            SDL_PollEvent(NULL);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);  // Keep the window open for 3 seconds

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete top;

    return 0;
}
