#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "common/defs.h"

// gameboy screen dimensions
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144


// acts as a wrapper for SDL_Window, and the display of the gameboy emulator
class Display
{
    private: 
        static RGB CLASSIC_PALLETE[4];
        static RGB GREY_PALLETE[4];
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool lcdEnabled;



    public:
        Display();
        ~Display();
        void update();
        void clear();
        // draw scan lin
        void drawScanLine();

};

