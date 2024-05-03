#include "display.h"
#include <iostream>
Display::Display()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "SDL Initialized" << std::endl;
    window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 5, SCREEN_HEIGHT * 5, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    // clear the display
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            display[x][y] = false;
        }
    }
}

Display::~Display()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::update()
{
    SDL_RenderPresent(renderer);
}

void Display::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            display[x][y] = false;
        }
    }
}

// xor the whole display with the sprite
void Display::setPixel(int x, int y, bool on)
{
    display[x][y] = on;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 1;
    rect.h = 1;
    if (on)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &rect);
}

bool Display::getPixel(int x, int y)
{
    return display[x][y];
}