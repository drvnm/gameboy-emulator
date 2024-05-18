#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "../common/defs.h"
#include "../memory/memory.h"
#include "../cpu/cpu.h"
#include "../debugger/debugger.h"


// gameboy screen dimensions
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

// window for rending vram tiles, plus space for gridlines
#define TILE_SCREEN_WIDTH 32 * 8 + 32
#define TILE_SCREEN_HEIGHT 32 * 8 + 32

enum VideoMode
{
    HBLANK = 0,
    VBLANK = 1,
    OAM = 2,
    VRAM = 3 
};

struct Pixel
{
    RGB color;
    int x, y;
};

// acts as a wrapper for SDL_Window, and the display of the gameboy emulator
class Display
{   
private:
    Memory *memory;
    CPU *cpu;
    Debugger *debugger;
    static RGB CLASSIC_PALLETE[4];
    static RGB GREY_PALLETE[4];
    static RGB CHILL_PALLETE[4]; // This pallete has chill colors, like light grey, light green, black and grey
    RGB pixels[SCREEN_HEIGHT * SCREEN_WIDTH] = {0};  // mirror 2d array of pixels
    SDL_Window *window;
    SDL_Window *tileWindow;
    SDL_Renderer *renderer;
    SDL_Renderer *tileRenderer;
    SDL_Texture *texture;
    int topLeftX, topLeftY;
    VideoMode mode;
    int scanlineCounter = 456;

    bool lcdEnabled();
    void updateFromMemory();
    void drawScanLine();
    void drawBackground();
    void drawSprites();
    void drawPixel(int x, int y, RGB color);
    void drawTiles(); // directly reads vram to draw all tiles on tilewindow
    void drawPixelTile(int x, int y, RGB color);
public:
    Display(Memory *memory, CPU *cpu, Debugger *debugger);
    ~Display();
    void update(uint8_t cycles);
    void clear();
    void renderCurrentFrame();
};
