#pragma once

#include <iostream>
#include <SDL2/SDL.h>
// gameboy screen dimensions
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

// acts as a wrapper for SDL_Window, and the display of the gameboy emulator
class Display
{
    private: 
        SDL_Window *window;
        SDL_Renderer *renderer;
        int display[SCREEN_WIDTH][SCREEN_HEIGHT];

    public:
        Display();
        ~Display();
        void update();
        void clear();
        void setPixel(int x, int y, bool on);
        bool getPixel(int x, int y);

};

