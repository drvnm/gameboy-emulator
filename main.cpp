// #include "display.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

#include "cartridge/cartridge.h"
#include "emulator/emulator.h"
#include "display/display.h"
#include "cpu/cpu.h"
#include "memory/memory.h"


int main(int argc, char *argv[])
{
    // read rom from command line
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom file>" << std::endl;
        return 1;
    }

    Cartridge* cartridge = new Cartridge(argv[1]);
    Memory* memory = new Memory(cartridge);
    CPU* cpu = new CPU(memory);
    Display* display = new Display(memory, cpu);
    
    Emulator emulator(cpu, display, memory, cartridge);
    emulator.run();



    // CPU cpu(rom);
    // cpu.execute();
    return 0;
}