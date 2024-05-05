// #include "display.h"
// #include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

#include "cpu/cpu.h"
#include "cartridge/cartridge.h"


int main(int argc, char *argv[])
{
    // read rome from command line
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom file>" << std::endl;
        return 1;
    }

    std::vector<uint8_t> rom;
    std::string romFile = argv[1];
    std::ifstream file(romFile, std::ios::binary);
    
    while (!file.eof())
    {
        uint8_t byte;
        file.read(reinterpret_cast<char *>(&byte), sizeof(byte));
        rom.push_back(byte);
    }

    Cartridge cartridge(rom);

    CPU cpu(rom);
    cpu.execute();
    return 0;



    // Display display;
    // SDL_Event event;
    // bool running = true;
    // while (running)
    // {
    //     while (SDL_PollEvent(&event))
    //     {
    //         if (event.type == SDL_QUIT)
    //         {
    //             running = false;
    //         }
    //     }
    // }
    // return 0;
}