#include "emulator.h"

Emulator::Emulator(CPU* cpu, Display* display, Memory* memory, Cartridge* cartridge) {
    this->cpu = cpu;
    this->display = display;
    this->memory = memory;
    this->cartridge = cartridge;
}


void Emulator::run() {
    while (cpu->registers.pc < memory->romSize) {
        // do interrupt handling
        uint8_t cycles = cpu->step();
        display->update(cycles);
        cpu->handleInterrupts();
    }
}