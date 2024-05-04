#include <iostream>

#include "cpu.h"

CPU::CPU(std::vector<uint8_t> rom) : rom(rom)
{
    registers.reset(); 
    setupOpcodes();

    // load the rom into memory
    for (int i = 0; i < rom.size(); i++)
    {
        memory[i] = rom[i];
    }
}

void CPU::execute()
{
    while (registers.pc < rom.size())
    {
        executeInstruction(rom[registers.pc]);
        registers.pc++;
    }
}

void CPU::executeInstruction(OPCODE opcode)
{
    std::cout << "Executing opcode: " << std::hex << (int)opcode << std::endl;
    (this->*opcodes[opcode])();
}

void CPU::setupOpcodes()
{
    // ADD INSTRUCTIONS
    opcodes[0x87] = &CPU::opcode0x87;
    opcodes[0x80] = &CPU::opcode0x80;
    opcodes[0x81] = &CPU::opcode0x81;
    opcodes[0x82] = &CPU::opcode0x82;
    opcodes[0x83] = &CPU::opcode0x83;
    opcodes[0x84] = &CPU::opcode0x84;
    opcodes[0x85] = &CPU::opcode0x85;
    opcodes[0x86] = &CPU::opcode0x86;
    opcodes[0xC6] = &CPU::opcode0xC6;

    // ADC INSTRUCTIONS
    opcodes[0x8F] = &CPU::opcode0x8F;
    opcodes[0x88] = &CPU::opcode0x88;
    opcodes[0x89] = &CPU::opcode0x89;
    opcodes[0x8A] = &CPU::opcode0x8A;
    opcodes[0x8B] = &CPU::opcode0x8B;
    opcodes[0x8C] = &CPU::opcode0x8C;
    opcodes[0x8D] = &CPU::opcode0x8D;
    opcodes[0x8E] = &CPU::opcode0x8E;
    opcodes[0xCE] = &CPU::opcode0xCE;

    // SUB INSTRUCTIONS
    opcodes[0x97] = &CPU::opcode0x97;
    opcodes[0x90] = &CPU::opcode0x90;
    opcodes[0x91] = &CPU::opcode0x91;
    opcodes[0x92] = &CPU::opcode0x92;
    opcodes[0x93] = &CPU::opcode0x93;
    opcodes[0x94] = &CPU::opcode0x94;
    opcodes[0x95] = &CPU::opcode0x95;
    opcodes[0x96] = &CPU::opcode0x96;
    opcodes[0xD6] = &CPU::opcode0xD6;

    // SBC INSTRUCTIONS
    opcodes[0x9F] = &CPU::opcode0x9F;
    opcodes[0x98] = &CPU::opcode0x98;
    opcodes[0x99] = &CPU::opcode0x99;
    opcodes[0x9A] = &CPU::opcode0x9A;
    opcodes[0x9B] = &CPU::opcode0x9B;
    opcodes[0x9C] = &CPU::opcode0x9C;
    opcodes[0x9D] = &CPU::opcode0x9D;
    opcodes[0x9E] = &CPU::opcode0x9E;
    opcodes[0xDE] = &CPU::opcode0xDE;

    // AND INSTRUCTIONS
    opcodes[0xA7] = &CPU::opcode0xA7;
    opcodes[0xA0] = &CPU::opcode0xA0;
    opcodes[0xA1] = &CPU::opcode0xA1;
    opcodes[0xA2] = &CPU::opcode0xA2;
    opcodes[0xA3] = &CPU::opcode0xA3;
    opcodes[0xA4] = &CPU::opcode0xA4;
    opcodes[0xA5] = &CPU::opcode0xA5;
    opcodes[0xA6] = &CPU::opcode0xA6;
    opcodes[0xE6] = &CPU::opcode0xE6;

    // OR INSTRUCTIONS
    opcodes[0xB7] = &CPU::opcode0xB7;
    opcodes[0xB0] = &CPU::opcode0xB0;
    opcodes[0xB1] = &CPU::opcode0xB1;
    opcodes[0xB2] = &CPU::opcode0xB2;
    opcodes[0xB3] = &CPU::opcode0xB3;
    opcodes[0xB4] = &CPU::opcode0xB4;
    opcodes[0xB5] = &CPU::opcode0xB5;
    opcodes[0xB6] = &CPU::opcode0xB6;
    opcodes[0xF6] = &CPU::opcode0xF6;

    // XOR INSTRUCTIONS
    opcodes[0xAF] = &CPU::opcode0xAF;
    opcodes[0xA8] = &CPU::opcode0xA8;
    opcodes[0xA9] = &CPU::opcode0xA9;
    opcodes[0xAA] = &CPU::opcode0xAA;
    opcodes[0xAB] = &CPU::opcode0xAB;
    opcodes[0xAC] = &CPU::opcode0xAC;
    opcodes[0xAD] = &CPU::opcode0xAD;
    opcodes[0xAE] = &CPU::opcode0xAE;
    opcodes[0xEE] = &CPU::opcode0xEE;

    // CP INSTRUCTIONS
    opcodes[0xBF] = &CPU::opcode0xBF;
    opcodes[0xB8] = &CPU::opcode0xB8;
    opcodes[0xB9] = &CPU::opcode0xB9;
    opcodes[0xBA] = &CPU::opcode0xBA;
    opcodes[0xBB] = &CPU::opcode0xBB;
    opcodes[0xBC] = &CPU::opcode0xBC;
    opcodes[0xBD] = &CPU::opcode0xBD;
    opcodes[0xBE] = &CPU::opcode0xBE;
    opcodes[0xFE] = &CPU::opcode0xFE;

    // INC INSTRUCTIONS
    opcodes[0x3C] = &CPU::opcode0x3C;
    opcodes[0x04] = &CPU::opcode0x04;
    opcodes[0x0C] = &CPU::opcode0x0C;
    opcodes[0x14] = &CPU::opcode0x14;
    opcodes[0x1C] = &CPU::opcode0x1C;
    opcodes[0x24] = &CPU::opcode0x24;
    opcodes[0x2C] = &CPU::opcode0x2C;
    opcodes[0x34] = &CPU::opcode0x34;

    // DEC INSTRUCTIONS
    opcodes[0x3D] = &CPU::opcode0x3D;
    opcodes[0x05] = &CPU::opcode0x05;
    opcodes[0x0D] = &CPU::opcode0x0D;
    opcodes[0x15] = &CPU::opcode0x15;
    opcodes[0x1D] = &CPU::opcode0x1D;
    opcodes[0x25] = &CPU::opcode0x25;
    opcodes[0x2D] = &CPU::opcode0x2D;
    opcodes[0x35] = &CPU::opcode0x35;

    // DAA and CPL INSTRUCTIONS
    opcodes[0x27] = &CPU::opcode0x27;
    opcodes[0x2F] = &CPU::opcode0x2F;

    










}

