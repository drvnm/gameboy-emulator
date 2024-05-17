#include "display.h"
#include <iostream>

RGB Display::CLASSIC_PALLETE[4] = {{155, 188, 15}, {139, 172, 15}, {48, 98, 48}, {15, 56, 15}};
RGB Display::GREY_PALLETE[4] = {{255, 255, 255}, {0xCC, 0xCC, 0xCC}, {0x77, 0x77, 0x77}, {0x0, 0x0, 0x0}};

Display::Display(Memory *memory, CPU *cpu, Debugger *debugger)
{
    this->memory = memory;
    this->cpu = cpu;
    this->debugger = debugger;
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "SDL Initialized" << std::endl;
    window = SDL_CreateWindow("VENUM Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 3, SCREEN_HEIGHT * 3, SDL_WINDOW_SHOWN);
    tileWindow = SDL_CreateWindow("Tile Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TILE_SCREEN_WIDTH * 3, TILE_SCREEN_HEIGHT * 3, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    tileRenderer = SDL_CreateRenderer(tileWindow, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderSetLogicalSize(tileRenderer, TILE_SCREEN_WIDTH, TILE_SCREEN_HEIGHT);

    clear();

    // draw a grid on the tile window
    SDL_SetRenderDrawColor(tileRenderer, 255, 255, 255, 255);
    for (int i = 0; i < 32; i++)
    {
        SDL_RenderDrawLine(tileRenderer, i * 8, 0, i * 8, 256);
        SDL_RenderDrawLine(tileRenderer, 0, i * 8, 256, i * 8);
    }
    SDL_RenderPresent(tileRenderer);
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
        // std::cout << "LCD is enabled and scanlineCounter is " << scanlineCounter << std::endl;
    }
    else
    {
        // memory->map[0xFF44] = 0;
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
            renderCurrentFrame();
            if (debugger->doTileRender)
            {
                drawTiles();
                SDL_RenderPresent(tileRenderer);
                debugger->doTileRender = false;
            }
            // print the frame buffer
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
            // std::cout << "Drawing scanline " << (int)currentScanline << std::endl;
            drawScanLine();
            // draw the frame buffer
        }
    }
}

void Display::drawScanLine()
{
    uint8_t lcdc = memory->readByte(0xFF40);
    if (bitIsSet(lcdc, 0))
    {
        drawBackground();
    }

    if (bitIsSet(lcdc, 1))
    {
        // drawSprites();
        // std::cout << "Drawing sprites" << std::endl;
    }
    else
    {
        // std::cout << "Not drawing sprites" << std::endl;
    }
}

void Display::drawBackground()
{
    uint8_t lcdc = memory->readByte(0xFF40);        // LCDC registerclks
    uint8_t scrollY = memory->readByte(0xFF42);     // scrollY is the Y position of the background (top left corner of the screen)
    uint8_t scrollX = memory->readByte(0xFF43);     // scrollX is the X position of the background (top left corner of the screen)
    uint8_t windowY = memory->readByte(0xFF4A);     // windowY is the Y position of the window (top left corner of the window)
    uint8_t windowX = memory->readByte(0xFF4B) - 7; // windowX is the X position of the window (top left corner of the window)
    uint8_t scanline = memory->readByte(0xFF44);    // scanline is the current scanline being drawn

    // print where the background should be drawn

    bool unsig = bitIsSet(lcdc, 4);                                  // if this bit is set, the tile data is unsigned (0x8000 to 0x8FFF), otherwise it is signed (0x8800 to 0x97FF
    uint16_t tileData = bitIsSet(lcdc, 4) ? 0x8000 : 0x8800;         // this is where the actual tile data is stored
    uint16_t backgroundMemory = bitIsSet(lcdc, 3) ? 0x9C00 : 0x9800; // this is where the background map is stored (each byte represents a tile number)
    uint8_t yPos = scrollY + scanline;                               // the y position of the pixel is the start of the background + the current scanline
    uint16_t tileRow = ((uint8_t)yPos / 8) * 32;                     // this moves us to the start of the map for this row of tiles

    for (int pixel = 0; pixel < 160; pixel++)
    {
        uint8_t xPos = pixel + scrollX;
        uint16_t tileCol = xPos / 8;
        uint16_t tileNum;
        uint16_t tileAddress = backgroundMemory + tileRow + tileCol; // address of the tile number
        if (unsig)
        {
            tileNum = memory->readByte(tileAddress);
        }
        else
        {
            int8_t signedTileNum = (int8_t)memory->readByte(tileAddress);
            tileNum = 256 + signedTileNum;
        }
        uint16_t tileLocation = tileData + (tileNum * 16);                // this gets the start of the tile data
        uint8_t line = yPos % 8;                                          // the line of the tile we are on
        uint16_t data1 = memory->readByte(tileLocation + (line * 2));     // get the first byte of the tile data
        uint16_t data2 = memory->readByte(tileLocation + (line * 2) + 1); // get the second byte of the tile data

        int colorBit = xPos % 8;                        // the bit of the tile we are on
        int colorNum = (data2 >> (7 - colorBit)) & 0x1; // get the color number
        colorNum <<= 1;                                 // shift the color number to the left by 1
        colorNum |= (data1 >> (7 - colorBit)) & 0x1;    // get the color number
        RGB color = CLASSIC_PALLETE[colorNum];
        pixels[(scanline * 160) + pixel] = color;
    }
}

void Display::drawTiles()
{
    uint16_t tileData = 0x8000;

    for (int tileY = 0; tileY < 32; tileY++)
    {
        for (int tileX = 0; tileX < 32; tileX++)
        {
            uint16_t tileLocation = tileData + (memory->readByte(0x9800 + (tileY * 32) + tileX) * 16);
            for (int row = 0; row < 8; row++)
            {
                uint8_t data1 = memory->readByte(tileLocation + (row * 2));
                uint8_t data2 = memory->readByte(tileLocation + (row * 2) + 1);
                if (data1 == 0 && data2 == 0)
                {
                    continue;
                }
                for (int col = 0; col < 8; col++)
                {
                    int colorBit = 1 << (7 - col);
                    int colorNum = ((data2 & colorBit) ? 1 : 0) << 1;
                    colorNum |= (data1 & colorBit) ? 1 : 0;
                    RGB color = CLASSIC_PALLETE[colorNum];
                    drawPixelTile(tileX * 8 + col, tileY * 8 + row, color);
                }
            }
        }
    }
}

void Display::drawPixelTile(int x, int y, RGB color)
{
    SDL_SetRenderDrawColor(tileRenderer, color.red, color.green, color.blue, 255);
    SDL_RenderDrawPoint(tileRenderer, x, y);
}

void Display::drawSprites()
{
   
}

void Display::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Display::renderCurrentFrame()
{
    SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(uint8_t) * 3);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}