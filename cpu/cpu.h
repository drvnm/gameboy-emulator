#pragma once

#include <vector>
#include <map>

#include "registers.h"
#include "instruction.h"

// emulates the CPU of the gameboy (the sharp LR35902)
class CPU
{
    std::vector<uint8_t> rom;
    short (CPU::*opcodes[0xFF])(); // array of function pointers to the opcodes
    Registers registers;           // 8-bit registers
    void setupOpcodes();           // sets up the opcodes
    // work ram
    OPCODE memory[0x2000]; // 8KB of work ram

    void executeInstruction(OPCODE instruction); // fetches and executes the instruction

    // ADD INSTRUCTIONS
    void add8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0x87(); // ADD A, AF.HIGH
    NUM_CYCLES opcode0x80(); // ADD A, BC.HIGH
    NUM_CYCLES opcode0x81(); // ADD A, BC.LOW
    NUM_CYCLES opcode0x82(); // ADD A, DE.HIGH
    NUM_CYCLES opcode0x83(); // ADD A, DE.LOW
    NUM_CYCLES opcode0x84(); // ADD A, HL.HIGH
    NUM_CYCLES opcode0x85(); // ADD A, HL.LOW
    NUM_CYCLES opcode0x86(); // ADD A, (HL)
    NUM_CYCLES opcode0xC6(); // ADD A, NUMBER
    // ADC INSTRUCTIONS
    void adc8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0x8F(); // ADC A, AF.HIGH
    NUM_CYCLES opcode0x88(); // ADC A, BC.HIGH
    NUM_CYCLES opcode0x89(); // ADC A, BC.LOW
    NUM_CYCLES opcode0x8A(); // ADC A, DE.HIGH
    NUM_CYCLES opcode0x8B(); // ADC A, DE.LOW
    NUM_CYCLES opcode0x8C(); // ADC A, HL.HIGH
    NUM_CYCLES opcode0x8D(); // ADC A, HL.LOW
    NUM_CYCLES opcode0x8E(); // ADC A, (HL)
    NUM_CYCLES opcode0xCE(); // ADC A, NUMBER
    // SUB INSTRUCTIONS
    void sub8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0x97(); // SUB A, AF.HIGH
    NUM_CYCLES opcode0x90(); // SUB A, BC.HIGH
    NUM_CYCLES opcode0x91(); // SUB A, BC.LOW
    NUM_CYCLES opcode0x92(); // SUB A, DE.HIGH
    NUM_CYCLES opcode0x93(); // SUB A, DE.LOW
    NUM_CYCLES opcode0x94(); // SUB A, HL.HIGH
    NUM_CYCLES opcode0x95(); // SUB A, HL.LOW
    NUM_CYCLES opcode0x96(); // SUB A, (HL)
    NUM_CYCLES opcode0xD6(); // SUB A, NUMBER
    // SBC INSTRUCTIONS
    void sbc8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0x9F(); // SBC A, AF.HIGH
    NUM_CYCLES opcode0x98(); // SBC A, BC.HIGH
    NUM_CYCLES opcode0x99(); // SBC A, BC.LOW
    NUM_CYCLES opcode0x9A(); // SBC A, DE.HIGH
    NUM_CYCLES opcode0x9B(); // SBC A, DE.LOW
    NUM_CYCLES opcode0x9C(); // SBC A, HL.HIGH
    NUM_CYCLES opcode0x9D(); // SBC A, HL.LOW
    NUM_CYCLES opcode0x9E(); // SBC A, (HL)
    NUM_CYCLES opcode0xDE(); // SBC A, NUMBER
    // AND INSTRUCTIONS
    void and8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0xA7(); // AND A, AF.HIGH
    NUM_CYCLES opcode0xA0(); // AND A, BC.HIGH
    NUM_CYCLES opcode0xA1(); // AND A, BC.LOW
    NUM_CYCLES opcode0xA2(); // AND A, DE.HIGH
    NUM_CYCLES opcode0xA3(); // AND A, DE.LOW
    NUM_CYCLES opcode0xA4(); // AND A, HL.HIGH
    NUM_CYCLES opcode0xA5(); // AND A, HL.LOW
    NUM_CYCLES opcode0xA6(); // AND A, (HL)
    NUM_CYCLES opcode0xE6(); // AND A, NUMBER
    // OR INSTRUCTIONS
    void or8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0xB7(); // OR A, AF.HIGH
    NUM_CYCLES opcode0xB0(); // OR A, BC.HIGH
    NUM_CYCLES opcode0xB1(); // OR A, BC.LOW
    NUM_CYCLES opcode0xB2(); // OR A, DE.HIGH
    NUM_CYCLES opcode0xB3(); // OR A, DE.LOW
    NUM_CYCLES opcode0xB4(); // OR A, HL.HIGH
    NUM_CYCLES opcode0xB5(); // OR A, HL.LOW
    NUM_CYCLES opcode0xB6(); // OR A, (HL)
    NUM_CYCLES opcode0xF6(); // OR A, NUMBER
    // XOR INSTRUCTIONS
    void xor8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0xAF(); // XOR A, AF.HIGH
    NUM_CYCLES opcode0xA8(); // XOR A, BC.HIGH
    NUM_CYCLES opcode0xA9(); // XOR A, BC.LOW
    NUM_CYCLES opcode0xAA(); // XOR A, DE.HIGH
    NUM_CYCLES opcode0xAB(); // XOR A, DE.LOW
    NUM_CYCLES opcode0xAC(); // XOR A, HL.HIGH
    NUM_CYCLES opcode0xAD(); // XOR A, HL.LOW
    NUM_CYCLES opcode0xAE(); // XOR A, (HL)
    NUM_CYCLES opcode0xEE(); // XOR A, NUMBER
    // CP INSTRUCTIONS
    void cp8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0xBF(); // CP A, AF.HIGH
    NUM_CYCLES opcode0xB8(); // CP A, BC.HIGH
    NUM_CYCLES opcode0xB9(); // CP A, BC.LOW
    NUM_CYCLES opcode0xBA(); // CP A, DE.HIGH
    NUM_CYCLES opcode0xBB(); // CP A, DE.LOW
    NUM_CYCLES opcode0xBC(); // CP A, HL.HIGH
    NUM_CYCLES opcode0xBD(); // CP A, HL.LOW
    NUM_CYCLES opcode0xBE(); // CP A, (HL)
    NUM_CYCLES opcode0xFE(); // CP A, NUMBER
    // INC INSTRUCTIONS
    void inc8bit(REGISTER *reg);
    NUM_CYCLES opcode0x3C(); // INC A
    NUM_CYCLES opcode0x04(); // INC B
    NUM_CYCLES opcode0x0C(); // INC C
    NUM_CYCLES opcode0x14(); // INC D
    NUM_CYCLES opcode0x1C(); // INC E
    NUM_CYCLES opcode0x24(); // INC H
    NUM_CYCLES opcode0x2C(); // INC L
    NUM_CYCLES opcode0x34(); // INC (HL)
    // DEC INSTRUCTIONS
    void dec8bit(REGISTER *reg);
    NUM_CYCLES opcode0x3D(); // DEC A
    NUM_CYCLES opcode0x05(); // DEC B
    NUM_CYCLES opcode0x0D(); // DEC C
    NUM_CYCLES opcode0x15(); // DEC D
    NUM_CYCLES opcode0x1D(); // DEC E
    NUM_CYCLES opcode0x25(); // DEC H
    NUM_CYCLES opcode0x2D(); // DEC L
    NUM_CYCLES opcode0x35(); // DEC (HL)
    // DAA INSTRUCTIONS
    NUM_CYCLES opcode0x27(); // DAA
    // CPL INSTRUCTIONS
    NUM_CYCLES opcode0x2F(); // CPL
    // CCF INSTRUCTIONS



public:
    CPU(std::vector<uint8_t> rom);
    void execute();
};
