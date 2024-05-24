#pragma once

#include "../common/defs.h"
#include "../cartridge/cartridge.h"
#include "../debugger/debugger.h"

class CPU;

// gameboy emulator memory map
#define MEM_SIZE 0x1000000

class Memory
{
private:
    Debugger *debugger;
    CPU *cpu;
    void reset();

public:
    int romSize;
    OPCODE map[MEM_SIZE] = {0};
    Memory(Cartridge *cartridge, Debugger *debugger);
    void setCPU(CPU *cpu);
    uint8_t readByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t value);
    void writeDirect(uint16_t address, uint8_t value);
    uint8_t readDirect(uint16_t address);

};