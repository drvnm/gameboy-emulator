// #include "display.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

#include "cartridge/cartridge.h"
#include "emulator/emulator.h"
#include "display/display.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "debugger/debugger.h"


int main(int argc, char *argv[])
{
    // read rom from command line
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom file>" << std::endl;
        return 1;
    }

    Debugger* debugger = new Debugger();
    Cartridge* cartridge = new Cartridge(argv[1], debugger);
    Memory* memory = new Memory(cartridge, debugger);
    CPU* cpu = new CPU(memory, debugger);
    Display* display = new Display(memory, cpu, debugger);
    Emulator emulator(cpu, display, memory, cartridge, debugger);
    emulator.run();



    // CPU cpu(rom);
    // cpu.execute();
    return 0;
}