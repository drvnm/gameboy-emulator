#include <iostream>

#include "cpu.h"

CPU::CPU(std::vector<uint8_t> rom) : rom(rom)
{
    reset();
    registers.reset();
    setupOpcodes();

    // load the rom into memory
    for (size_t i = 0; i < rom.size(); i++)
    {
        memory[i] = rom[i];
    }
}

void CPU::reset()
{
    // TIMA, TMA, TAC
    for (int i = 0xFF05; i <= 0xFF07; i++)
    {
        memory[i] = 0x00;
    }

    memory[0xFF25] = 0xF3; // NR51
    memory[0xFF26] = 0x00; // idk ??
    memory[0xFF40] = 0x91; // LCDC control
    memory[0xFF42] = 0x00; // SCY
    memory[0xFF43] = 0x00; // SCX
    memory[0xFF45] = 0x00; // LYC
    memory[0xFF47] = 0xFC; // BGP
    memory[0xFF48] = 0xFF; // OBP0
    memory[0xFF49] = 0xFF; // OBP1
    memory[0xFF4A] = 0x00; // WY
    memory[0xFF4B] = 0x00; // WX
    memory[0xFFFF] = 0x00; // IE
}

void CPU::execute()
{
    while (registers.pc < rom.size())
    {
        OPCODE opcode = rom[registers.pc];
        executeInstruction(opcode);
        registers.pc += 1;
    }
}

void CPU::executeInstruction(OPCODE opcode)
{
    if (opcodes[opcode] != nullptr)
    {
        uint8_t firstByte, secondByte;
        if (opcodeDescriptionTable[opcode].size == 1)
        {
            firstByte = rom[registers.pc + 1];
            std::cout << "Executing opcode: " << std::hex << (int)opcode << " at address: " << std::hex << registers.pc << " Instruction: " << opcodeDescriptionTable[opcode].name << " " << std::hex << (int)firstByte << std::endl;
        }
        else if (opcodeDescriptionTable[opcode].size == 2)
        {
            firstByte = rom[registers.pc + 1];
            secondByte = rom[registers.pc + 2];
            std::cout << "Executing opcode: " << std::hex << (int)opcode << " at address: " << std::hex << registers.pc << " Instruction: " << opcodeDescriptionTable[opcode].name << " " << std::hex << (int)firstByte << " " << std::hex << (int)secondByte << std::endl;
        } else {
            std::cout << "Executing opcode: " << std::hex << (int)opcode << " at address: " << std::hex << registers.pc << " Instruction: " << opcodeDescriptionTable[opcode].name << std::endl;
        }
        (this->*opcodes[opcode])();
    }
    else
    {
        std::cout << "Opcode not implemented" << std::endl;
        throw std::runtime_error("Opcode not implemented");
    }
}

void CPU::setupOpcodes()
{
    // LOAD INSTRUCTIONS
    opcodes[0x7F] = &CPU::opcode0x7F;
    opcodes[0x78] = &CPU::opcode0x78;
    opcodes[0x79] = &CPU::opcode0x79;
    opcodes[0x7A] = &CPU::opcode0x7A;
    opcodes[0x7B] = &CPU::opcode0x7B;
    opcodes[0x7C] = &CPU::opcode0x7C;
    opcodes[0x7D] = &CPU::opcode0x7D;
    opcodes[0x7E] = &CPU::opcode0x7E;
    opcodes[0x3E] = &CPU::opcode0x3E;
    opcodes[0x47] = &CPU::opcode0x47;
    opcodes[0x40] = &CPU::opcode0x40;
    opcodes[0x41] = &CPU::opcode0x41;
    opcodes[0x42] = &CPU::opcode0x42;
    opcodes[0x43] = &CPU::opcode0x43;
    opcodes[0x44] = &CPU::opcode0x44;
    opcodes[0x45] = &CPU::opcode0x45;
    opcodes[0x46] = &CPU::opcode0x46;
    opcodes[0x06] = &CPU::opcode0x06;
    opcodes[0x4F] = &CPU::opcode0x4F;
    opcodes[0x48] = &CPU::opcode0x48;
    opcodes[0x49] = &CPU::opcode0x49;
    opcodes[0x4A] = &CPU::opcode0x4A;
    opcodes[0x4B] = &CPU::opcode0x4B;
    opcodes[0x4C] = &CPU::opcode0x4C;
    opcodes[0x4D] = &CPU::opcode0x4D;
    opcodes[0x4E] = &CPU::opcode0x4E;
    opcodes[0x0E] = &CPU::opcode0x0E;
    opcodes[0x57] = &CPU::opcode0x57;
    opcodes[0x50] = &CPU::opcode0x50;
    opcodes[0x51] = &CPU::opcode0x51;
    opcodes[0x52] = &CPU::opcode0x52;
    opcodes[0x53] = &CPU::opcode0x53;
    opcodes[0x54] = &CPU::opcode0x54;
    opcodes[0x55] = &CPU::opcode0x55;
    opcodes[0x56] = &CPU::opcode0x56;
    opcodes[0x16] = &CPU::opcode0x16;
    opcodes[0x5F] = &CPU::opcode0x5F;
    opcodes[0x58] = &CPU::opcode0x58;
    opcodes[0x59] = &CPU::opcode0x59;
    opcodes[0x5A] = &CPU::opcode0x5A;
    opcodes[0x5B] = &CPU::opcode0x5B;
    opcodes[0x5C] = &CPU::opcode0x5C;
    opcodes[0x5D] = &CPU::opcode0x5D;
    opcodes[0x5E] = &CPU::opcode0x5E;
    opcodes[0x1E] = &CPU::opcode0x1E;
    opcodes[0x67] = &CPU::opcode0x67;
    opcodes[0x60] = &CPU::opcode0x60;
    opcodes[0x61] = &CPU::opcode0x61;
    opcodes[0x62] = &CPU::opcode0x62;
    opcodes[0x63] = &CPU::opcode0x63;
    opcodes[0x64] = &CPU::opcode0x64;
    opcodes[0x65] = &CPU::opcode0x65;
    opcodes[0x66] = &CPU::opcode0x66;
    opcodes[0x26] = &CPU::opcode0x26;
    opcodes[0x6F] = &CPU::opcode0x6F;
    opcodes[0x68] = &CPU::opcode0x68;
    opcodes[0x69] = &CPU::opcode0x69;
    opcodes[0x6A] = &CPU::opcode0x6A;
    opcodes[0x6B] = &CPU::opcode0x6B;
    opcodes[0x6C] = &CPU::opcode0x6C;
    opcodes[0x6D] = &CPU::opcode0x6D;
    opcodes[0x6E] = &CPU::opcode0x6E;
    opcodes[0x2E] = &CPU::opcode0x2E;
    opcodes[0x77] = &CPU::opcode0x77;
    opcodes[0x70] = &CPU::opcode0x70;
    opcodes[0x71] = &CPU::opcode0x71;
    opcodes[0x72] = &CPU::opcode0x72;
    opcodes[0x73] = &CPU::opcode0x73;
    opcodes[0x74] = &CPU::opcode0x74;
    opcodes[0x75] = &CPU::opcode0x75;
    opcodes[0x36] = &CPU::opcode0x36;
    opcodes[0x0A] = &CPU::opcode0x0A;
    opcodes[0x1A] = &CPU::opcode0x1A;
    opcodes[0xFA] = &CPU::opcode0xFA;
    opcodes[0x02] = &CPU::opcode0x02;
    opcodes[0x12] = &CPU::opcode0x12;
    opcodes[0xEA] = &CPU::opcode0xEA;
    opcodes[0xF0] = &CPU::opcode0xF0;
    opcodes[0xE0] = &CPU::opcode0xE0;
    opcodes[0xF2] = &CPU::opcode0xF2;
    opcodes[0xE2] = &CPU::opcode0xE2;
    opcodes[0x3A] = &CPU::opcode0x3A;
    opcodes[0x32] = &CPU::opcode0x32;
    opcodes[0x2A] = &CPU::opcode0x2A;
    opcodes[0x22] = &CPU::opcode0x22;

    // 16-BIT LOAD INSTRUCTIONS
    opcodes[0x01] = &CPU::opcode0x01;
    opcodes[0x11] = &CPU::opcode0x11;
    opcodes[0x21] = &CPU::opcode0x21;
    opcodes[0x31] = &CPU::opcode0x31;
    opcodes[0xF9] = &CPU::opcode0xF9;

    // PUSH AND POP INSTRUCTIONS
    opcodes[0xF5] = &CPU::opcode0xF5;
    opcodes[0xC5] = &CPU::opcode0xC5;
    opcodes[0xD5] = &CPU::opcode0xD5;
    opcodes[0xE5] = &CPU::opcode0xE5;
    opcodes[0xF1] = &CPU::opcode0xF1;
    opcodes[0xC1] = &CPU::opcode0xC1;
    opcodes[0xD1] = &CPU::opcode0xD1;
    opcodes[0xE1] = &CPU::opcode0xE1;

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

    // CONTROL INSTRUCTIONS
    opcodes[0x3F] = &CPU::opcode0x3F;
    opcodes[0x37] = &CPU::opcode0x37;
    opcodes[0x00] = &CPU::opcode0x00;
    opcodes[0x76] = &CPU::opcode0x76;
    opcodes[0x10] = &CPU::opcode0x10;
    opcodes[0xF3] = &CPU::opcode0xF3;
    opcodes[0xFB] = &CPU::opcode0xFB;

    // DAA and CPL INSTRUCTIONS
    opcodes[0x27] = &CPU::opcode0x27;
    opcodes[0x2F] = &CPU::opcode0x2F;

    // JUMP INSTRUCTIONS
    opcodes[0xC3] = &CPU::opcode0xC3;
    opcodes[0xC2] = &CPU::opcode0xC2;
    opcodes[0xCA] = &CPU::opcode0xCA;
    opcodes[0xD2] = &CPU::opcode0xD2;
    opcodes[0xDA] = &CPU::opcode0xDA;
    opcodes[0x18] = &CPU::opcode0x18;
    opcodes[0x20] = &CPU::opcode0x20;
    opcodes[0x28] = &CPU::opcode0x28;
    opcodes[0x30] = &CPU::opcode0x30;
    opcodes[0x38] = &CPU::opcode0x38;

    // CALL INSTRUCTIONS
    opcodes[0xCD] = &CPU::opcode0xCD;
    opcodes[0xC4] = &CPU::opcode0xC4;
    opcodes[0xCC] = &CPU::opcode0xCC;
    opcodes[0xD4] = &CPU::opcode0xD4;
    opcodes[0xDC] = &CPU::opcode0xDC;

    // RETURN INSTRUCTIONS
    opcodes[0xC9] = &CPU::opcode0xC9;
    opcodes[0xC0] = &CPU::opcode0xC0;
    opcodes[0xC8] = &CPU::opcode0xC8;
    opcodes[0xD0] = &CPU::opcode0xD0;
    opcodes[0xD8] = &CPU::opcode0xD8;
    // opcodes[0xD9] = &CPU::opcode0xD9; NOT IMPLEMENTED YET
    opcodes[0xC7] = &CPU::opcode0xC7;
    opcodes[0xCF] = &CPU::opcode0xCF;
    opcodes[0xD7] = &CPU::opcode0xD7;
    opcodes[0xE7] = &CPU::opcode0xE7;
    opcodes[0xEF] = &CPU::opcode0xEF;
    opcodes[0xF7] = &CPU::opcode0xF7;
    opcodes[0xFF] = &CPU::opcode0xFF;
}

// stack operations
void CPU::push(uint16_t value)
{
    memory[registers.sp - 1] = (value >> 8) & 0xFF;
    memory[registers.sp - 2] = value & 0xFF;
    registers.sp -= 2;
}

uint16_t CPU::pop()
{
    uint16_t value = memory[registers.sp] | (memory[registers.sp + 1] << 8);
    registers.sp += 2;
    return value;
}

uint16_t CPU::load16BitFromPC()
{
    uint8_t low = rom[registers.pc + 1];
    uint8_t high = rom[registers.pc + 2];
    return (high << 8) | low;
}