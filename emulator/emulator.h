#pragma once

#include "../cpu/cpu.h"
#include "../display/display.h"
#include "../cartridge/cartridge.h"
#include "../memory/memory.h"

class Emulator
{
private:
    CPU *cpu;
    Memory *memory;
    Display *display;
    Cartridge *cartridge;


public:
    Emulator(CPU *cpu, Display *display, Memory *memory, Cartridge *cartridge);
    void run();
};