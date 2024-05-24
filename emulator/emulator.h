#pragma once

#include "../cpu/cpu.h"
#include "../display/display.h"
#include "../cartridge/cartridge.h"
#include "../memory/memory.h"
#include "../debugger/debugger.h"

#define MAX_CYCLES 69905  
const float FPS = 59.73f;
const float DELAY_TIME = 1000.0f / FPS;

class Emulator
{
private:
    CPU *cpu;
    Memory *memory;
    Display *display;
    Cartridge *cartridge;
    Debugger *debugger;

public:
    Emulator(CPU *cpu, Display *display, Memory *memory, Cartridge *cartridge, Debugger *debugger);
    void run();
};