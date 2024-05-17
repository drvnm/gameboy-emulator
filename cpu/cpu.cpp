#include <iostream>

#include "cpu.h"
#include "../memory/memory.h"

#define REQUIRE(condition, message)        \
    if (!(condition))                      \
    {                                      \
        std::cerr << message << std::endl; \
        throw std::runtime_error(message); \
    }

CPU::CPU(Memory *memory, Debugger *debugger)
{
    this->memory = memory;
    this->debugger = debugger;
    reset();
    setupOpcodes();
}

void CPU::reset()
{
    
}

void CPU::requestInterrupt(uint8_t interrupt)
{
    uint8_t interruptFlag = memory->readByte(0xFF0F);
    interruptFlag = setBit(interruptFlag, interrupt);
    memory->writeByte(0xFF0F, interruptFlag);
}

void CPU::serviceInterrupt(uint8_t interrupt)
{
    halted = false;
    registers.ime = false;
    uint8_t interruptFlag = memory->readByte(0xFF0F);
    interruptFlag = clearBit(interruptFlag, interrupt);
    memory->writeByte(0xFF0F, interruptFlag);

    push(registers.pc);
    switch (interrupt)
    {
    case 0:
        registers.pc = 0x40;
        break;
    case 1:
        registers.pc = 0x48;
        break;
    case 2:
        registers.pc = 0x50;
        break;
    case 3:
        registers.pc = 0x58;
        break;
    case 4:
        registers.pc = 0x60;
        break;
    default:
        break;
    }
}

void CPU::handleInterrupts()
{
    uint8_t interruptFlag = memory->readByte(0xFF0F);
    uint8_t interruptEnable = memory->readByte(0xFFFF);

    if (interruptFlag <= 0) {
        if(halted) halted = false;
        return;
    }
    if (!registers.ime)
        return;
    for (int i = 0; i < 5; i++)
    {
        if (bitIsSet(interruptFlag, i))
        {
            if (bitIsSet(interruptEnable, i))
            {
                serviceInterrupt(i);
            }
        }
    }
}

uint8_t CPU::step()
{
    OPCODE opcode = memory->readByte(registers.pc);
    uint8_t cycles = executeInstruction(opcode);
    registers.pc += 1;
    return cycles;
}

uint8_t CPU::executeInstruction(OPCODE opcode)
{
    if (opcode == 0xCB)
    {
        OPCODE extendedOpcode = memory->readByte(registers.pc + 1);
        if (extendedOpcodes[extendedOpcode] != nullptr)
        {
            // read instruction from opcode table
            if (debugger->doPrint)
                std::cout << "Executing extended opcode: " << std::hex << (int)extendedOpcode << " at address: " << std::hex << registers.pc << " Instruction: " << extendedOpcodeDescriptionTable[extendedOpcode].name << std::endl;
            short cycles = (this->*extendedOpcodes[extendedOpcode])();
            registers.pc += 1; // to account for the extended opcode
            return cycles;
        }
        else
        {
            if (debugger->doPrint)
                std::cout << "Extended opcode " << std::hex << (int)extendedOpcode << " not implemented at address: " << std::hex << registers.pc << std::endl;
            throw std::runtime_error("Extended opcode not implemented");
        }
    }
    if (opcodes[opcode] != nullptr)
    {
        uint8_t firstByte, secondByte;
        if (opcodeDescriptionTable[opcode].size == 1)
        {
            firstByte = memory->map[registers.pc + 1];
            if (debugger->doPrint)
                std::cout << "Executing opcode: " << std::hex << (int)opcode << " at address: " << std::hex << registers.pc << " Instruction: " << opcodeDescriptionTable[opcode].name << " " << std::hex << (int)firstByte << std::endl;
        }
        else if (opcodeDescriptionTable[opcode].size == 2)
        {
            firstByte = memory->map[registers.pc + 1];
            secondByte = memory->map[registers.pc + 2];
            if (debugger->doPrint)
                std::cout << "Executing opcode: " << std::hex << (int)opcode << " at address: " << std::hex << registers.pc << " Instruction: " << opcodeDescriptionTable[opcode].name << " " << std::hex << (int)firstByte << " " << std::hex << (int)secondByte << std::endl;
        }
        else
        {
            if (debugger->doPrint)
                std::cout << "Executing opcode: " << std::hex << (int)opcode << " at address: " << std::hex << registers.pc << " Instruction: " << opcodeDescriptionTable[opcode].name << std::endl;
        }
        return (this->*opcodes[opcode])();
    }
    else
    {
        std::cout << "Opcode " << std::hex << (int)opcode << " not implemented at address: " << std::hex << registers.pc << std::endl;
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
    opcodes[0xF8] = &CPU::opcode0xF8;
    opcodes[0x08] = &CPU::opcode0x08;

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

    // ADD 16-BIT INSTRUCTIONS
    opcodes[0x09] = &CPU::opcode0x09;
    opcodes[0x19] = &CPU::opcode0x19;
    opcodes[0x29] = &CPU::opcode0x29;
    opcodes[0x39] = &CPU::opcode0x39;
    opcodes[0xE8] = &CPU::opcode0xE8;

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

    // 16-BIT INC
    opcodes[0x03] = &CPU::opcode0x03;
    opcodes[0x13] = &CPU::opcode0x13;
    opcodes[0x23] = &CPU::opcode0x23;
    opcodes[0x33] = &CPU::opcode0x33;

    // DEC INSTRUCTIONS
    opcodes[0x3D] = &CPU::opcode0x3D;
    opcodes[0x05] = &CPU::opcode0x05;
    opcodes[0x0D] = &CPU::opcode0x0D;
    opcodes[0x15] = &CPU::opcode0x15;
    opcodes[0x1D] = &CPU::opcode0x1D;
    opcodes[0x25] = &CPU::opcode0x25;
    opcodes[0x2D] = &CPU::opcode0x2D;
    opcodes[0x35] = &CPU::opcode0x35;

    // 16-BIT DEC
    opcodes[0x0B] = &CPU::opcode0x0B;
    opcodes[0x1B] = &CPU::opcode0x1B;
    opcodes[0x2B] = &CPU::opcode0x2B;
    opcodes[0x3B] = &CPU::opcode0x3B;

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
    opcodes[0xE9] = &CPU::opcode0xE9;

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
    opcodes[0xD9] = &CPU::opcode0xD9;
    opcodes[0xC7] = &CPU::opcode0xC7;
    opcodes[0xCF] = &CPU::opcode0xCF;
    opcodes[0xD7] = &CPU::opcode0xD7;
    opcodes[0xDF] = &CPU::opcode0xDF;
    opcodes[0xE7] = &CPU::opcode0xE7;
    opcodes[0xEF] = &CPU::opcode0xEF;
    opcodes[0xF7] = &CPU::opcode0xF7;
    opcodes[0xFF] = &CPU::opcode0xFF;

    // NON EXTENDED ROTATE INSTRUCTIONS
    opcodes[0x07] = &CPU::opcode0x07;
    opcodes[0x17] = &CPU::opcode0x17;
    opcodes[0x0F] = &CPU::opcode0x0F;
    opcodes[0x1F] = &CPU::opcode0x1F;

    // EXTENDED OPCODES
    extendedOpcodes[0x00] = &CPU::extendedOpcode0x00; // RLC B
    extendedOpcodes[0x01] = &CPU::extendedOpcode0x01; // RLC C
    extendedOpcodes[0x02] = &CPU::extendedOpcode0x02; // RLC D
    extendedOpcodes[0x03] = &CPU::extendedOpcode0x03; // RLC E
    extendedOpcodes[0x04] = &CPU::extendedOpcode0x04; // RLC H
    extendedOpcodes[0x05] = &CPU::extendedOpcode0x05; // RLC L
    extendedOpcodes[0x06] = &CPU::extendedOpcode0x06; // RLC (HL)
    extendedOpcodes[0x07] = &CPU::extendedOpcode0x07; // RLC A

    extendedOpcodes[0x08] = &CPU::extendedOpcode0x08; // RRC B
    extendedOpcodes[0x09] = &CPU::extendedOpcode0x09; // RRC C
    extendedOpcodes[0x0A] = &CPU::extendedOpcode0x0A; // RRC D
    extendedOpcodes[0x0B] = &CPU::extendedOpcode0x0B; // RRC E
    extendedOpcodes[0x0C] = &CPU::extendedOpcode0x0C; // RRC H
    extendedOpcodes[0x0D] = &CPU::extendedOpcode0x0D; // RRC L
    extendedOpcodes[0x0E] = &CPU::extendedOpcode0x0E; // RRC (HL)
    extendedOpcodes[0x0F] = &CPU::extendedOpcode0x0F; // RRC A

    extendedOpcodes[0x10] = &CPU::extendedOpcode0x10; // rl B
    extendedOpcodes[0x11] = &CPU::extendedOpcode0x11; // rl C
    extendedOpcodes[0x12] = &CPU::extendedOpcode0x12; // rl D
    extendedOpcodes[0x13] = &CPU::extendedOpcode0x13; // rl E
    extendedOpcodes[0x14] = &CPU::extendedOpcode0x14; // rl H
    extendedOpcodes[0x15] = &CPU::extendedOpcode0x15; // rl L
    extendedOpcodes[0x16] = &CPU::extendedOpcode0x16; // rl (HL)
    extendedOpcodes[0x17] = &CPU::extendedOpcode0x17; // rl A

    extendedOpcodes[0x18] = &CPU::extendedOpcode0x18; // rr B
    extendedOpcodes[0x19] = &CPU::extendedOpcode0x19; // rr C
    extendedOpcodes[0x1A] = &CPU::extendedOpcode0x1A; // rr D
    extendedOpcodes[0x1B] = &CPU::extendedOpcode0x1B; // rr E
    extendedOpcodes[0x1C] = &CPU::extendedOpcode0x1C; // rr H
    extendedOpcodes[0x1D] = &CPU::extendedOpcode0x1D; // rr L
    extendedOpcodes[0x1E] = &CPU::extendedOpcode0x1E; // rr (HL)
    extendedOpcodes[0x1F] = &CPU::extendedOpcode0x1F; // rr A

    extendedOpcodes[0x20] = &CPU::extendedOpcode0x20; // sla B
    extendedOpcodes[0x21] = &CPU::extendedOpcode0x21; // sla C
    extendedOpcodes[0x22] = &CPU::extendedOpcode0x22; // sla D
    extendedOpcodes[0x23] = &CPU::extendedOpcode0x23; // sla E
    extendedOpcodes[0x24] = &CPU::extendedOpcode0x24; // sla H
    extendedOpcodes[0x25] = &CPU::extendedOpcode0x25; // sla L
    extendedOpcodes[0x26] = &CPU::extendedOpcode0x26; // sla (HL)
    extendedOpcodes[0x27] = &CPU::extendedOpcode0x27; // sla A

    extendedOpcodes[0x28] = &CPU::extendedOpcode0x28; // sra B
    extendedOpcodes[0x29] = &CPU::extendedOpcode0x29; // sra C
    extendedOpcodes[0x2A] = &CPU::extendedOpcode0x2A; // sra D
    extendedOpcodes[0x2B] = &CPU::extendedOpcode0x2B; // sra E
    extendedOpcodes[0x2C] = &CPU::extendedOpcode0x2C; // sra H
    extendedOpcodes[0x2D] = &CPU::extendedOpcode0x2D; // sra L
    extendedOpcodes[0x2E] = &CPU::extendedOpcode0x2E; // sra (HL)
    extendedOpcodes[0x2F] = &CPU::extendedOpcode0x2F; // sra A

    extendedOpcodes[0x30] = &CPU::extendedOpcode0x30; // swap B
    extendedOpcodes[0x31] = &CPU::extendedOpcode0x31; // swap C
    extendedOpcodes[0x32] = &CPU::extendedOpcode0x32; // swap D
    extendedOpcodes[0x33] = &CPU::extendedOpcode0x33; // swap E
    extendedOpcodes[0x34] = &CPU::extendedOpcode0x34; // swap H
    extendedOpcodes[0x35] = &CPU::extendedOpcode0x35; // swap L
    extendedOpcodes[0x36] = &CPU::extendedOpcode0x36; // swap (HL)
    extendedOpcodes[0x37] = &CPU::extendedOpcode0x37; // swap A

    extendedOpcodes[0x38] = &CPU::extendedOpcode0x38; // SRL B
    extendedOpcodes[0x39] = &CPU::extendedOpcode0x39; // SRL C
    extendedOpcodes[0x3A] = &CPU::extendedOpcode0x3A; // SRL D
    extendedOpcodes[0x3B] = &CPU::extendedOpcode0x3B; // SRL E
    extendedOpcodes[0x3C] = &CPU::extendedOpcode0x3C; // SRL H
    extendedOpcodes[0x3D] = &CPU::extendedOpcode0x3D; // SRL L
    extendedOpcodes[0x3E] = &CPU::extendedOpcode0x3E; // SRL (HL)
    extendedOpcodes[0x3F] = &CPU::extendedOpcode0x3F; // SRL A

    extendedOpcodes[0x40] = &CPU::extendedOpcode0x40; // bit 0, B
    extendedOpcodes[0x41] = &CPU::extendedOpcode0x41; // bit 0, C
    extendedOpcodes[0x42] = &CPU::extendedOpcode0x42; // bit 0, D
    extendedOpcodes[0x43] = &CPU::extendedOpcode0x43; // bit 0, E
    extendedOpcodes[0x44] = &CPU::extendedOpcode0x44; // bit 0, H
    extendedOpcodes[0x45] = &CPU::extendedOpcode0x45; // bit 0, L
    extendedOpcodes[0x46] = &CPU::extendedOpcode0x46; // bit 0, (HL)
    extendedOpcodes[0x47] = &CPU::extendedOpcode0x47; // bit 0, A

    extendedOpcodes[0x48] = &CPU::extendedOpcode0x48; // bit 1, B
    extendedOpcodes[0x49] = &CPU::extendedOpcode0x49; // bit 1, C
    extendedOpcodes[0x4A] = &CPU::extendedOpcode0x4A; // bit 1, D
    extendedOpcodes[0x4B] = &CPU::extendedOpcode0x4B; // bit 1, E
    extendedOpcodes[0x4C] = &CPU::extendedOpcode0x4C; // bit 1, H
    extendedOpcodes[0x4D] = &CPU::extendedOpcode0x4D; // bit 1, L
    extendedOpcodes[0x4E] = &CPU::extendedOpcode0x4E; // bit 1, (HL)
    extendedOpcodes[0x4F] = &CPU::extendedOpcode0x4F; // bit 1, A

    extendedOpcodes[0x50] = &CPU::extendedOpcode0x50; // bit 2, B
    extendedOpcodes[0x51] = &CPU::extendedOpcode0x51; // bit 2, C
    extendedOpcodes[0x52] = &CPU::extendedOpcode0x52; // bit 2, D
    extendedOpcodes[0x53] = &CPU::extendedOpcode0x53; // bit 2, E
    extendedOpcodes[0x54] = &CPU::extendedOpcode0x54; // bit 2, H
    extendedOpcodes[0x55] = &CPU::extendedOpcode0x55; // bit 2, L
    extendedOpcodes[0x56] = &CPU::extendedOpcode0x56; // bit 2, (HL)
    extendedOpcodes[0x57] = &CPU::extendedOpcode0x57; // bit 2, A

    extendedOpcodes[0x58] = &CPU::extendedOpcode0x58; // bit 3, B
    extendedOpcodes[0x59] = &CPU::extendedOpcode0x59; // bit 3, C
    extendedOpcodes[0x5A] = &CPU::extendedOpcode0x5A; // bit 3, D
    extendedOpcodes[0x5B] = &CPU::extendedOpcode0x5B; // bit 3, E
    extendedOpcodes[0x5C] = &CPU::extendedOpcode0x5C; // bit 3, H
    extendedOpcodes[0x5D] = &CPU::extendedOpcode0x5D; // bit 3, L
    extendedOpcodes[0x5E] = &CPU::extendedOpcode0x5E; // bit 3, (HL)
    extendedOpcodes[0x5F] = &CPU::extendedOpcode0x5F; // bit 3, A

    extendedOpcodes[0x60] = &CPU::extendedOpcode0x60; // bit 4, B
    extendedOpcodes[0x61] = &CPU::extendedOpcode0x61; // bit 4, C
    extendedOpcodes[0x62] = &CPU::extendedOpcode0x62; // bit 4, D
    extendedOpcodes[0x63] = &CPU::extendedOpcode0x63; // bit 4, E
    extendedOpcodes[0x64] = &CPU::extendedOpcode0x64; // bit 4, H
    extendedOpcodes[0x65] = &CPU::extendedOpcode0x65; // bit 4, L
    extendedOpcodes[0x66] = &CPU::extendedOpcode0x66; // bit 4, (HL)
    extendedOpcodes[0x67] = &CPU::extendedOpcode0x67; // bit 4, A

    extendedOpcodes[0x68] = &CPU::extendedOpcode0x68; // bit 5, B
    extendedOpcodes[0x69] = &CPU::extendedOpcode0x69; // bit 5, C
    extendedOpcodes[0x6A] = &CPU::extendedOpcode0x6A; // bit 5, D
    extendedOpcodes[0x6B] = &CPU::extendedOpcode0x6B; // bit 5, E
    extendedOpcodes[0x6C] = &CPU::extendedOpcode0x6C; // bit 5, H
    extendedOpcodes[0x6D] = &CPU::extendedOpcode0x6D; // bit 5, L
    extendedOpcodes[0x6E] = &CPU::extendedOpcode0x6E; // bit 5, (HL)
    extendedOpcodes[0x6F] = &CPU::extendedOpcode0x6F; // bit 5, A

    extendedOpcodes[0x70] = &CPU::extendedOpcode0x70; // bit 6, B
    extendedOpcodes[0x71] = &CPU::extendedOpcode0x71; // bit 6, C
    extendedOpcodes[0x72] = &CPU::extendedOpcode0x72; // bit 6, D
    extendedOpcodes[0x73] = &CPU::extendedOpcode0x73; // bit 6, E
    extendedOpcodes[0x74] = &CPU::extendedOpcode0x74; // bit 6, H
    extendedOpcodes[0x75] = &CPU::extendedOpcode0x75; // bit 6, L
    extendedOpcodes[0x76] = &CPU::extendedOpcode0x76; // bit 6, (HL)
    extendedOpcodes[0x77] = &CPU::extendedOpcode0x77; // bit 6, A

    extendedOpcodes[0x78] = &CPU::extendedOpcode0x78; // bit 7, B
    extendedOpcodes[0x79] = &CPU::extendedOpcode0x79; // bit 7, C
    extendedOpcodes[0x7A] = &CPU::extendedOpcode0x7A; // bit 7, D
    extendedOpcodes[0x7B] = &CPU::extendedOpcode0x7B; // bit 7, E
    extendedOpcodes[0x7C] = &CPU::extendedOpcode0x7C; // bit 7, H
    extendedOpcodes[0x7D] = &CPU::extendedOpcode0x7D; // bit 7, L
    extendedOpcodes[0x7E] = &CPU::extendedOpcode0x7E; // bit 7, (HL)
    extendedOpcodes[0x7F] = &CPU::extendedOpcode0x7F; // bit 7, A

    extendedOpcodes[0x80] = &CPU::extendedOpcode0x80; // res 0, B
    extendedOpcodes[0x81] = &CPU::extendedOpcode0x81; // res 0, C
    extendedOpcodes[0x82] = &CPU::extendedOpcode0x82; // res 0, D
    extendedOpcodes[0x83] = &CPU::extendedOpcode0x83; // res 0, E
    extendedOpcodes[0x84] = &CPU::extendedOpcode0x84; // res 0, H
    extendedOpcodes[0x85] = &CPU::extendedOpcode0x85; // res 0, L
    extendedOpcodes[0x86] = &CPU::extendedOpcode0x86; // res 0, (HL)
    extendedOpcodes[0x87] = &CPU::extendedOpcode0x87; // res 0, A

    extendedOpcodes[0x88] = &CPU::extendedOpcode0x88; // res 1, B
    extendedOpcodes[0x89] = &CPU::extendedOpcode0x89; // res 1, C
    extendedOpcodes[0x8A] = &CPU::extendedOpcode0x8A; // res 1, D
    extendedOpcodes[0x8B] = &CPU::extendedOpcode0x8B; // res 1, E
    extendedOpcodes[0x8C] = &CPU::extendedOpcode0x8C; // res 1, H
    extendedOpcodes[0x8D] = &CPU::extendedOpcode0x8D; // res 1, L
    extendedOpcodes[0x8E] = &CPU::extendedOpcode0x8E; // res 1, (HL)
    extendedOpcodes[0x8F] = &CPU::extendedOpcode0x8F; // res 1, A

    extendedOpcodes[0x90] = &CPU::extendedOpcode0x90; // res 2, B
    extendedOpcodes[0x91] = &CPU::extendedOpcode0x91; // res 2, C
    extendedOpcodes[0x92] = &CPU::extendedOpcode0x92; // res 2, D
    extendedOpcodes[0x93] = &CPU::extendedOpcode0x93; // res 2, E
    extendedOpcodes[0x94] = &CPU::extendedOpcode0x94; // res 2, H
    extendedOpcodes[0x95] = &CPU::extendedOpcode0x95; // res 2, L
    extendedOpcodes[0x96] = &CPU::extendedOpcode0x96; // res 2, (HL)
    extendedOpcodes[0x97] = &CPU::extendedOpcode0x97; // res 2, A

    extendedOpcodes[0x98] = &CPU::extendedOpcode0x98; // res 3, B
    extendedOpcodes[0x99] = &CPU::extendedOpcode0x99; // res 3, C
    extendedOpcodes[0x9A] = &CPU::extendedOpcode0x9A; // res 3, D
    extendedOpcodes[0x9B] = &CPU::extendedOpcode0x9B; // res 3, E
    extendedOpcodes[0x9C] = &CPU::extendedOpcode0x9C; // res 3, H
    extendedOpcodes[0x9D] = &CPU::extendedOpcode0x9D; // res 3, L
    extendedOpcodes[0x9E] = &CPU::extendedOpcode0x9E; // res 3, (HL)
    extendedOpcodes[0x9F] = &CPU::extendedOpcode0x9F; // res 3, A

    extendedOpcodes[0xA0] = &CPU::extendedOpcode0xA0; // res 4, B
    extendedOpcodes[0xA1] = &CPU::extendedOpcode0xA1; // res 4, C
    extendedOpcodes[0xA2] = &CPU::extendedOpcode0xA2; // res 4, D
    extendedOpcodes[0xA3] = &CPU::extendedOpcode0xA3; // res 4, E
    extendedOpcodes[0xA4] = &CPU::extendedOpcode0xA4; // res 4, H
    extendedOpcodes[0xA5] = &CPU::extendedOpcode0xA5; // res 4, L
    extendedOpcodes[0xA6] = &CPU::extendedOpcode0xA6; // res 4, (HL)
    extendedOpcodes[0xA7] = &CPU::extendedOpcode0xA7; // res 4, A

    extendedOpcodes[0xA8] = &CPU::extendedOpcode0xA8; // res 5, B
    extendedOpcodes[0xA9] = &CPU::extendedOpcode0xA9; // res 5, C
    extendedOpcodes[0xAA] = &CPU::extendedOpcode0xAA; // res 5, D
    extendedOpcodes[0xAB] = &CPU::extendedOpcode0xAB; // res 5, E
    extendedOpcodes[0xAC] = &CPU::extendedOpcode0xAC; // res 5, H
    extendedOpcodes[0xAD] = &CPU::extendedOpcode0xAD; // res 5, L
    extendedOpcodes[0xAE] = &CPU::extendedOpcode0xAE; // res 5, (HL)
    extendedOpcodes[0xAF] = &CPU::extendedOpcode0xAF; // res 5, A

    extendedOpcodes[0xB0] = &CPU::extendedOpcode0xB0; // res 6, B
    extendedOpcodes[0xB1] = &CPU::extendedOpcode0xB1; // res 6, C
    extendedOpcodes[0xB2] = &CPU::extendedOpcode0xB2; // res 6, D
    extendedOpcodes[0xB3] = &CPU::extendedOpcode0xB3; // res 6, E
    extendedOpcodes[0xB4] = &CPU::extendedOpcode0xB4; // res 6, H
    extendedOpcodes[0xB5] = &CPU::extendedOpcode0xB5; // res 6, L
    extendedOpcodes[0xB6] = &CPU::extendedOpcode0xB6; // res 6, (HL)
    extendedOpcodes[0xB7] = &CPU::extendedOpcode0xB7; // res 6, A

    extendedOpcodes[0xB8] = &CPU::extendedOpcode0xB8; // res 7, B
    extendedOpcodes[0xB9] = &CPU::extendedOpcode0xB9; // res 7, C
    extendedOpcodes[0xBA] = &CPU::extendedOpcode0xBA; // res 7, D
    extendedOpcodes[0xBB] = &CPU::extendedOpcode0xBB; // res 7, E
    extendedOpcodes[0xBC] = &CPU::extendedOpcode0xBC; // res 7, H
    extendedOpcodes[0xBD] = &CPU::extendedOpcode0xBD; // res 7, L
    extendedOpcodes[0xBE] = &CPU::extendedOpcode0xBE; // res 7, (HL)
    extendedOpcodes[0xBF] = &CPU::extendedOpcode0xBF; // res 7, A

    extendedOpcodes[0xC0] = &CPU::extendedOpcode0xC0; // set 0, B
    extendedOpcodes[0xC1] = &CPU::extendedOpcode0xC1; // set 0, C
    extendedOpcodes[0xC2] = &CPU::extendedOpcode0xC2; // set 0, D
    extendedOpcodes[0xC3] = &CPU::extendedOpcode0xC3; // set 0, E
    extendedOpcodes[0xC4] = &CPU::extendedOpcode0xC4; // set 0, H
    extendedOpcodes[0xC5] = &CPU::extendedOpcode0xC5; // set 0, L
    extendedOpcodes[0xC6] = &CPU::extendedOpcode0xC6; // set 0, (HL)
    extendedOpcodes[0xC7] = &CPU::extendedOpcode0xC7; // set 0, A

    extendedOpcodes[0xC8] = &CPU::extendedOpcode0xC8; // set 1, B
    extendedOpcodes[0xC9] = &CPU::extendedOpcode0xC9; // set 1, C
    extendedOpcodes[0xCA] = &CPU::extendedOpcode0xCA; // set 1, D
    extendedOpcodes[0xCB] = &CPU::extendedOpcode0xCB; // set 1, E
    extendedOpcodes[0xCC] = &CPU::extendedOpcode0xCC; // set 1, H
    extendedOpcodes[0xCD] = &CPU::extendedOpcode0xCD; // set 1, L
    extendedOpcodes[0xCE] = &CPU::extendedOpcode0xCE; // set 1, (HL)
    extendedOpcodes[0xCF] = &CPU::extendedOpcode0xCF; // set 1, A

    extendedOpcodes[0xD0] = &CPU::extendedOpcode0xD0; // set 2, B
    extendedOpcodes[0xD1] = &CPU::extendedOpcode0xD1; // set 2, C
    extendedOpcodes[0xD2] = &CPU::extendedOpcode0xD2; // set 2, D
    extendedOpcodes[0xD3] = &CPU::extendedOpcode0xD3; // set 2, E
    extendedOpcodes[0xD4] = &CPU::extendedOpcode0xD4; // set 2, H
    extendedOpcodes[0xD5] = &CPU::extendedOpcode0xD5; // set 2, L
    extendedOpcodes[0xD6] = &CPU::extendedOpcode0xD6; // set 2, (HL)
    extendedOpcodes[0xD7] = &CPU::extendedOpcode0xD7; // set 2, A

    extendedOpcodes[0xD8] = &CPU::extendedOpcode0xD8; // set 3, B
    extendedOpcodes[0xD9] = &CPU::extendedOpcode0xD9; // set 3, C
    extendedOpcodes[0xDA] = &CPU::extendedOpcode0xDA; // set 3, D
    extendedOpcodes[0xDB] = &CPU::extendedOpcode0xDB; // set 3, E
    extendedOpcodes[0xDC] = &CPU::extendedOpcode0xDC; // set 3, H
    extendedOpcodes[0xDD] = &CPU::extendedOpcode0xDD; // set 3, L
    extendedOpcodes[0xDE] = &CPU::extendedOpcode0xDE; // set 3, (HL)
    extendedOpcodes[0xDF] = &CPU::extendedOpcode0xDF; // set 3, A

    extendedOpcodes[0xE0] = &CPU::extendedOpcode0xE0; // set 4, B
    extendedOpcodes[0xE1] = &CPU::extendedOpcode0xE1; // set 4, C
    extendedOpcodes[0xE2] = &CPU::extendedOpcode0xE2; // set 4, D
    extendedOpcodes[0xE3] = &CPU::extendedOpcode0xE3; // set 4, E
    extendedOpcodes[0xE4] = &CPU::extendedOpcode0xE4; // set 4, H
    extendedOpcodes[0xE5] = &CPU::extendedOpcode0xE5; // set 4, L
    extendedOpcodes[0xE6] = &CPU::extendedOpcode0xE6; // set 4, (HL)
    extendedOpcodes[0xE7] = &CPU::extendedOpcode0xE7; // set 4, A

    extendedOpcodes[0xE8] = &CPU::extendedOpcode0xE8; // set 5, B
    extendedOpcodes[0xE9] = &CPU::extendedOpcode0xE9; // set 5, C
    extendedOpcodes[0xEA] = &CPU::extendedOpcode0xEA; // set 5, D
    extendedOpcodes[0xEB] = &CPU::extendedOpcode0xEB; // set 5, E
    extendedOpcodes[0xEC] = &CPU::extendedOpcode0xEC; // set 5, H
    extendedOpcodes[0xED] = &CPU::extendedOpcode0xED; // set 5, L
    extendedOpcodes[0xEE] = &CPU::extendedOpcode0xEE; // set 5, (HL)
    extendedOpcodes[0xEF] = &CPU::extendedOpcode0xEF; // set 5, A

    extendedOpcodes[0xF0] = &CPU::extendedOpcode0xF0; // set 6, B
    extendedOpcodes[0xF1] = &CPU::extendedOpcode0xF1; // set 6, C
    extendedOpcodes[0xF2] = &CPU::extendedOpcode0xF2; // set 6, D
    extendedOpcodes[0xF3] = &CPU::extendedOpcode0xF3; // set 6, E
    extendedOpcodes[0xF4] = &CPU::extendedOpcode0xF4; // set 6, H
    extendedOpcodes[0xF5] = &CPU::extendedOpcode0xF5; // set 6, L
    extendedOpcodes[0xF6] = &CPU::extendedOpcode0xF6; // set 6, (HL)
    extendedOpcodes[0xF7] = &CPU::extendedOpcode0xF7; // set 6, A

    extendedOpcodes[0xF8] = &CPU::extendedOpcode0xF8; // set 7, B
    extendedOpcodes[0xF9] = &CPU::extendedOpcode0xF9; // set 7, C
    extendedOpcodes[0xFA] = &CPU::extendedOpcode0xFA; // set 7, D
    extendedOpcodes[0xFB] = &CPU::extendedOpcode0xFB; // set 7, E
    extendedOpcodes[0xFC] = &CPU::extendedOpcode0xFC; // set 7, H
    extendedOpcodes[0xFD] = &CPU::extendedOpcode0xFD; // set 7, L
    extendedOpcodes[0xFE] = &CPU::extendedOpcode0xFE; // set 7, (HL)
    extendedOpcodes[0xFF] = &CPU::extendedOpcode0xFF; // set 7, A
}

// stack operations
void CPU::push(uint16_t value)
{
    memory->writeByte(registers.sp - 1, (value >> 8) & 0xFF);
    memory->writeByte(registers.sp - 2, value & 0xFF);
    registers.sp -= 2;
}

uint16_t CPU::pop()
{
    uint8_t low = memory->readByte(registers.sp);
    uint8_t high = memory->readByte(registers.sp + 1);
    uint16_t value = (high << 8) | low;
    registers.sp += 2;
    return value;
}

uint16_t CPU::load16BitFromPC()
{
    uint8_t low = memory->readByte(registers.pc + 1);
    uint8_t high = memory->readByte(registers.pc + 2);
    return (high << 8) | low;
}

void CPU::runJSONtests(nlohmann::json_abi_v3_11_3::json tests)
{
    std::cout << "Running tests" << std::endl;
    std::cout << "Number of tests: " << tests.size() << std::endl;
    for (auto &test : tests)
    {
        auto initialStates = test["initial"];
        registers.pc = initialStates["pc"];
        registers.sp = initialStates["sp"];
        registers.a = initialStates["a"];
        registers.b = initialStates["b"];
        registers.c = initialStates["c"];
        registers.d = initialStates["d"];
        registers.e = initialStates["e"];
        registers.f = initialStates["f"];
        registers.h = initialStates["h"];
        registers.l = initialStates["l"];

        auto ramStates = initialStates["ram"];
        for (auto &ramState : ramStates)
        {
            memory->writeByte(ramState[0], ramState[1]);
        }

        auto cycles = test["cycles"];
        for (auto &cycle : cycles)
        {
            if (std::string(cycle[2]).at(0) == 'r')
                memory->writeByte(cycle[0], cycle[1]);
            // if(std::string(test["name"]) == "F0 021E") {
            //     // read memory
            //     std::cout << "Reading memory at: " << cycle[0] << " Value: " << (int)memory->readByte(cycle[0]) << std::endl;
            // }
        }
        step();
        auto finalStates = test["final"];
        if (registers.pc != finalStates["pc"])
        {
            std::cout << "Failed test: " << test["name"] << " PC" << std::endl;
            std::cout << "Expected: " << finalStates["pc"] << " Got: " << registers.pc << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " PC: " << registers.pc << " Expected: " << finalStates["pc"] << std::endl;
        }
        if (registers.sp != finalStates["sp"])
        {
            std::cout << "Failed test: " << test["name"] << " SP" << std::endl;
            std::cout << "Expected: " << finalStates["sp"] << " Got: " << registers.sp << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " SP: " << registers.sp << " Expected: " << finalStates["sp"] << std::endl;
        }
        if (registers.a != finalStates["a"])
        {
            std::cout << "Failed test: " << test["name"] << " A" << std::endl;
            std::cout << "Expected: " << finalStates["a"] << " Got: " << (int)registers.a << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " A: " << (int)registers.a << " Expected: " << finalStates["a"] << std::endl;
        }
        if (registers.b != finalStates["b"])
        {
            std::cout << "Failed test: " << test["name"] << " B" << std::endl;
            std::cout << "Expected: " << finalStates["b"] << " Got: " << (int)registers.b << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " B: " << (int)registers.b << " Expected: " << finalStates["b"] << std::endl;
        }
        if (registers.c != finalStates["c"])
        {
            std::cout << "Failed test: " << test["name"] << " C" << std::endl;
            std::cout << "Expected: " << finalStates["c"] << " Got: " << (int)registers.c << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " C: " << (int)registers.c << " Expected: " << finalStates["c"] << std::endl;
        }
        if (registers.d != finalStates["d"])
        {
            std::cout << "Failed test: " << test["name"] << " D" << std::endl;
            std::cout << "Expected: " << finalStates["d"] << " Got: " << (int)registers.d << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " D: " << (int)registers.d << " Expected: " << finalStates["d"] << std::endl;
        }
        if (registers.e != finalStates["e"])
        {
            std::cout << "Failed test: " << test["name"] << " E" << std::endl;
            std::cout << "Expected: " << finalStates["e"] << " Got: " << (int)registers.e << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " E: " << (int)registers.e << " Expected: " << finalStates["e"] << std::endl;
        }
        if (registers.f != finalStates["f"])
        {
            std::cout << "Failed test: " << test["name"] << " F" << std::endl;
            std::cout << "Expected: " << finalStates["f"] << " Got: " << (int)registers.f << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " F: " << (int)registers.f << " Expected: " << finalStates["f"] << std::endl;
        }
        if (registers.h != finalStates["h"])
        {
            std::cout << "Failed test: " << test["name"] << " H" << std::endl;
            std::cout << "Expected: " << finalStates["h"] << " Got: " << (int)registers.h << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " H: " << (int)registers.h << " Expected: " << finalStates["h"] << std::endl;
        }
        if (registers.l != finalStates["l"])
        {
            std::cout << "Failed test: " << test["name"] << " L" << std::endl;
            std::cout << "Expected: " << finalStates["l"] << " Got: " << (int)registers.l << std::endl;
        }
        else
        {
            // std::cout << "Passed test: " << test["name"] << " L: " << (int)registers.l << " Expected: " << finalStates["l"] << std::endl;
        }
        auto finalRamState = finalStates["ram"];
        for (auto &ramState : finalRamState)
        {
            // if(std::string(test["name"]) == "F0 021E") {
            //     // read memory
            //     std::cout << "Reading memory at: " << ramState[0] << " Value: " << (int)memory->readByte(ramState[0]) << std::endl;
            // }
            if (memory->readByte(ramState[0]) != ramState[1])
            {
                std::cout << "Failed test: " << test["name"] << " RAM" << std::endl;
                std::cout << "Expected: " << ramState[1] << " Got: " << (int)memory->readByte(ramState[0]) << std::endl;
            }
            else
            {
                // std::cout << "Passed test: " << test["name"] << " RAM: " << (int)memory->readByte(ramState[0]) << " Expected: " << ramState[1] << std::endl;
            }
        }
    }
}

bool CPU::clockIsEnabled()
{
    return bitIsSet(memory->readByte(TMC), 2);
}

uint8_t CPU::readClockFrequency()
{
    return memory->readByte(TMC) & 0x3;
}

void CPU::setClockFrequency()
{
    uint8_t clockFrequency = readClockFrequency();
    switch (clockFrequency)
    {
    case 0:
        timerCounter = 1024;
        break;
    case 1:
        timerCounter = 16;
        break;
    case 2:
        timerCounter = 64;
        break;
    case 3:
        timerCounter = 256;
        break;
    }
}

void CPU::updateTimers(int cycles)
{
    doDividerRegister(cycles);

    if (clockIsEnabled())
    {
        timerCounter -= cycles;

        if (timerCounter <= 0)
        {
            setClockFrequency();

            // if timer is about to overflow
            if (memory->readByte(TIMA) == 0xFF)
            {
                memory->writeByte(TIMA, memory->readByte(TMA)); // reload the timer
                requestInterrupt(2);
            }
            else
            {
                memory->writeByte(TIMA, memory->readByte(TIMA) + 1); // increment the timer
            }
        }
    }
}

void CPU::doDividerRegister(int cycles)
{
    divReg += cycles;
    if (divCounter >= 255)
    {
        divCounter = 0;
        memory->map[0xFF04]++;
    }
}