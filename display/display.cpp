#include "display.h"
#include <iostream>

RGB Display::CLASSIC_PALLETE[4] = {{155, 188, 15}, {139, 172, 15}, {48, 98, 48}, {15, 56, 15}};
RGB Display::GREY_PALLETE[4] = {{255, 255, 255}, {0xCC, 0xCC, 0xCC}, {0x77, 0x77, 0x77}, {0x0, 0x0, 0x0}};

Display::Display(Memory *memory, CPU *cpu)
{
    this->memory = memory;
    this->cpu = cpu;
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "SDL Initialized" << std::endl;
    window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH , SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Display::~Display()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::lcdEnabled()
{
    return bitIsSet(memory->readByte(0xFF40), 7);
}

void Display::updateFromMemory()
{
    uint8_t stat = memory->readByte(0xFF41); // According to the Gameboy docs, the STAT register is at 0xFF41

    if (!lcdEnabled())
    {
        scanlineCounter = 456;
        memory->map[0xFF44] = 0;
        stat &= 252; // Clear the lower 2 bits of the STAT register
        stat = setBit(stat, 0);
        memory->writeByte(0xFF41, stat);
        return;
    }

    uint8_t currentScanline = memory->readByte(0xFF44);
    uint8_t currentMode = stat & 0x3;

    uint8_t mode = 0;
    bool requestInterrupt = false;

    if (currentScanline >= 144)
    {
        mode = VideoMode::VBLANK; // Set the mode to VBLANK
        stat = setBit(stat, 0);
        stat = clearBit(stat, 1);
        requestInterrupt = bitIsSet(stat, 4);
    }
    else
    {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        if (scanlineCounter >= mode2bounds)
        {
            mode = VideoMode::OAM;
            stat = setBit(stat, 1);
            stat = clearBit(stat, 0);
            requestInterrupt = bitIsSet(stat, 5);
        }
        else if (scanlineCounter >= mode3bounds)
        {
            mode = VideoMode::VRAM;
            stat = setBit(stat, 1);
            stat = setBit(stat, 0);
        }
        else
        {
            mode = VideoMode::HBLANK;
            stat = clearBit(stat, 1);
            stat = clearBit(stat, 0);
            requestInterrupt = bitIsSet(stat, 3);
        }
    }

    if (requestInterrupt && (mode != currentMode)) // if the mode has changed and the interrupt is requested
    {
        cpu->requestInterrupt(1);
    }

    // check the conincidence flag
    if (memory->readByte(0xFF44) == memory->readByte(0xFF45))
    {
        stat = setBit(stat, 2);
        if (bitIsSet(stat, 6))
        {
            cpu->requestInterrupt(1);
        }
    }
    else
    {
        stat = clearBit(stat, 2);
    }
    memory->writeByte(0xFF41, stat);
}

// basically just says, if the LCD is enabled, and the scanline is between 0 and 143, draw the scanline
void Display::update(uint8_t cycles)
{
    updateFromMemory();
    if (lcdEnabled())
    {
        scanlineCounter -= cycles;
        std::cout << "LCD is enabled and scanlineCounter is " << scanlineCounter << std::endl;
    }
    else
    {
        std::cout << "LCD is not enabled" << std::endl;
        return;
    }
    if (scanlineCounter <= 0)
    {
        // move to the next scanline
        memory->map[0xFF44]++;
        uint8_t currentScanline = memory->readByte(0xFF44);
        scanlineCounter = 456;
        if (currentScanline == 144)
        {
            cpu->requestInterrupt(0);
            // set the vblank interrupt
            memory->writeByte(0xFF0F, memory->readByte(0xFF0F) | 0x01);
        }
        else if (currentScanline > 153)
        {
            memory->map[0xFF44] = 0;
        }
        else if (currentScanline < 144)
        {
            std::cout << "Drawing scanline " << (int)currentScanline << std::endl;
            drawScanLine();
        } else {
            clear();
        }
    }

   
    // SDL_RenderPresent(renderer);
}

void Display::drawScanLine()
{
    uint8_t lcdc = memory->readByte(0xFF40);
    if (bitIsSet(lcdc, 0))
    {
        drawBackground();
        std::cout << "Drawing background" << std::endl;
    }

    if (bitIsSet(lcdc, 1))
    {
        drawSprites();
        std::cout << "Drawing sprites" << std::endl;
    } else {
        std::cout << "Not drawing sprites" << std::endl;
    }
}

void Display::drawBackground()
{
    uint8_t lcdc = memory->readByte(0xFF40);
    uint8_t scrollY = memory->readByte(0xFF42);
    uint8_t scrollX = memory->readByte(0xFF43);
    uint8_t windowY = memory->readByte(0xFF4A);
    uint8_t windowX = memory->readByte(0xFF4B) - 7;
    
    // print the current scanline
    std::cout << "Drawing scanline " << (int)memory->readByte(0xFF44) << std::endl;

    // print where the background should be drawn
    std::cout << "Drawing background at (" << (int)scrollX << ", " << (int)scrollY << ")" << std::endl;

    // print the window position
    
}

void Display::drawSprites()
{
}

void Display::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
