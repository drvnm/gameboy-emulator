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

struct Pixel
{
    uint8_t r, g, b;
    int x, y;
};

// acts as a wrapper for SDL_Window, and the display of the gameboy emulator
class Display
{
private:
    Memory *memory;
    CPU *cpu;
    // mirror 2d array of pixels
    Pixel pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
    static RGB CLASSIC_PALLETE[4];
    static RGB GREY_PALLETE[4];
    SDL_Window *window;
    SDL_Renderer *renderer;
    int topLeftX, topLeftY;
    VideoMode mode;
    int scanlineCounter = 456;

    bool lcdEnabled();
    void updateFromMemory();
    void drawScanLine();
    void drawBackground();
    void drawSprites();
public:
    Display(Memory *memory, CPU *cpu);
    ~Display();
    void update(uint8_t cycles);
    void clear();
    // draw scan lin
};
