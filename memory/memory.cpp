#include "memory.h"
#include "../cpu/cpu.h"
#include <iostream>

Memory::Memory(Cartridge *cartridge, Debugger *debugger)
{
    this->debugger = debugger;
    reset();
    romSize = cartridge->rom.size();
    std::cout << "rom size: " << romSize << std::endl;
    for (size_t i = 0; i < cartridge->rom.size(); i++)
    {
        map[i] = cartridge->rom[i];
    }
}

void Memory::setCPU(CPU *cpu)
{
    this->cpu = cpu;
}

void Memory::reset()
{
    map[0xFF05] = 0x00;
    map[0xFF06] = 0x00;
    map[0xFF07] = 0x00;
    map[0xFF0F] = 0xE1;
    map[0xFF10] = 0x80;
    map[0xFF11] = 0xBF;
    map[0xFF12] = 0xF3;
    map[0xFF14] = 0xBF;
    map[0xFF16] = 0x3F;
    map[0xFF17] = 0x00;
    map[0xFF19] = 0xBF;
    map[0xFF1A] = 0x7F;
    map[0xFF1B] = 0xFF;
    map[0xFF1C] = 0x9F;
    map[0xFF1E] = 0xBF;
    map[0xFF20] = 0xFF;
    map[0xFF21] = 0x00;
    map[0xFF22] = 0x00;
    map[0xFF23] = 0xBF;
    map[0xFF24] = 0x77;
    map[0xFF25] = 0xF3;
    map[0xFF26] = 0xF1;
    map[0xFF40] = 0x91;
    map[0xFF42] = 0x00;
    map[0xFF43] = 0x00;
    map[0xFF45] = 0x00;
    map[0xFF47] = 0xFC;
    map[0xFF48] = 0xFF;
    map[0xFF49] = 0xFF;
    map[0xFF4A] = 0x00;
    map[0xFF4B] = 0x00;
    map[0xFFFF] = 0x00;
}

uint8_t Memory::readByte(uint16_t address)
{
    return map[address];
}

void Memory::writeByte(uint16_t address, uint8_t value)
{
    if (address == 0xFF46) // DMA Transfer
    {
        map[address] = value;
        for (int i = 0; i < 0xA0; i++)
        {
            map[0xFE00 + i] = map[(value << 8) + i];
        }
    }
    else if (address == TMC)
    {
        uint8_t currentfreq = cpu->readClockFrequency();
        map[address] = value;
        uint8_t newfreq = cpu->readClockFrequency();
        if (currentfreq != newfreq)
        {
            cpu->setClockFrequency();
        }
    }
    // else if (address == 0xFF44)
    // {
    //     map[address] = 0;
    // }
    // else if (address == 0xFF00)
    // {
    //     map[address] = 1;
    // }
    else
    {

        map[address] = value;
    }

    if (address == 0xFF02 && value == 0x81)
    {
        std::cout << (char)map[0xFF01];
    }
}
// }