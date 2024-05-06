#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "../common/defs.h"
#include "../memory/memory.h"
#include "../cpu/cpu.h"

// gameboy screen dimensions
#define SCREEN_WIDTH 265
#define SCREEN_HEIGHT 265

enum VideoMode
{
    HBLANK = 0,
    VBLANK = 1,
    OAM = 2,
    VRAM = 3
};

// acts as a wrapper for SDL_Window, and the display of the gameboy emulator
class Display
{
private:
    Memory *memory;
    CPU *cpu;
    static RGB CLASSIC_PALLETE[4];
    static RGB GREY_PALLETE[4];
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool lcdEnabled();
    int topLeftX, topLeftY;
    VideoMode mode;
    int scanlineCounter = 456;

    void updateFromMemory();
public:
    Display(Memory *memory, CPU *cpu);
    ~Display();
    void update(uint8_t cycles);
    void clear();
    // draw scan lin
    void drawScanLine();
};
