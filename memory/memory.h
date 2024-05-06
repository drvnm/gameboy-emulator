#pragma once

#include "../common/defs.h"
#include "../cartridge/cartridge.h"

// gameboy emulator memory map
#define MEM_SIZE 0x10000

class Memory
{
private:
    void reset();

public:
    int romSize;
    OPCODE map[MEM_SIZE];
    Memory(Cartridge *cartridge);
    uint8_t readByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t value);

};