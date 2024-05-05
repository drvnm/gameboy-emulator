#include "display.h"
#include <iostream>

RGB Display::CLASSIC_PALLETE[4] = { { 155,188,15 }, { 139,172,15 }, { 48,98,48 }, { 15,56,15 } };
RGB Display::GREY_PALLETE[4] = { { 255,255,255 },{ 0xCC,0xCC,0xCC },{ 0x77,0x77,0x77 }, { 0x0,0x0,0x0 } };


Display::Display()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "SDL Initialized" << std::endl;
    window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 5, SCREEN_HEIGHT * 5, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  
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

   
}
