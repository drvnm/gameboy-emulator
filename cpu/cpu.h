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
    uint8_t memory[0xFFFF];        // 64KB of memory

    void executeInstruction(OPCODE instruction); // fetches and executes the instruction

    // stack operations
    void push(uint16_t value);
    uint16_t pop();

    // helper functions
    uint16_t load16BitFromPC();

    // NO OP
    NUM_CYCLES opcode0x00();
    
    // LOAD INSTRUCTIONS
    void load8bit(REGISTER *reg, uint8_t value);
    NUM_CYCLES opcode0x7F(); // LD A, AF.HIGH
    NUM_CYCLES opcode0x78(); // LD A, BC.HIGH
    NUM_CYCLES opcode0x79(); // LD A, BC.LOW
    NUM_CYCLES opcode0x7A(); // LD A, DE.HIGH
    NUM_CYCLES opcode0x7B(); // LD A, DE.LOW
    NUM_CYCLES opcode0x7C(); // LD A, HL.HIGH
    NUM_CYCLES opcode0x7D(); // LD A, HL.LOW
    NUM_CYCLES opcode0x7E(); // LD A, (HL)
    NUM_CYCLES opcode0x3E(); // LD A, NUMBER
    NUM_CYCLES opcode0x47(); // LD B, AF.HIGH
    NUM_CYCLES opcode0x40(); // LD B, BC.HIGH
    NUM_CYCLES opcode0x41(); // LD B, BC.LOW
    NUM_CYCLES opcode0x42(); // LD B, DE.HIGH
    NUM_CYCLES opcode0x43(); // LD B, DE.LOW
    NUM_CYCLES opcode0x44(); // LD B, HL.HIGH
    NUM_CYCLES opcode0x45(); // LD B, HL.LOW
    NUM_CYCLES opcode0x46(); // LD B, (HL)
    NUM_CYCLES opcode0x06(); // LD B, NUMBER
    NUM_CYCLES opcode0x4F(); // LD C, AF.HIGH
    NUM_CYCLES opcode0x48(); // LD C, BC.HIGH
    NUM_CYCLES opcode0x49(); // LD C, BC.LOW
    NUM_CYCLES opcode0x4A(); // LD C, DE.HIGH
    NUM_CYCLES opcode0x4B(); // LD C, DE.LOW
    NUM_CYCLES opcode0x4C(); // LD C, HL.HIGH
    NUM_CYCLES opcode0x4D(); // LD C, HL.LOW
    NUM_CYCLES opcode0x4E(); // LD C, (HL)
    NUM_CYCLES opcode0x0E(); // LD C, NUMBER
    NUM_CYCLES opcode0x57(); // LD D, AF.HIGH
    NUM_CYCLES opcode0x50(); // LD D, BC.HIGH
    NUM_CYCLES opcode0x51(); // LD D, BC.LOW
    NUM_CYCLES opcode0x52(); // LD D, DE.HIGH
    NUM_CYCLES opcode0x53(); // LD D, DE.LOW
    NUM_CYCLES opcode0x54(); // LD D, HL.HIGH
    NUM_CYCLES opcode0x55(); // LD D, HL.LOW
    NUM_CYCLES opcode0x56(); // LD D, (HL)
    NUM_CYCLES opcode0x16(); // LD D, NUMBER
    NUM_CYCLES opcode0x5F(); // LD E, AF.HIGH
    NUM_CYCLES opcode0x58(); // LD E, BC.HIGH
    NUM_CYCLES opcode0x59(); // LD E, BC.LOW
    NUM_CYCLES opcode0x5A(); // LD E, DE.HIGH
    NUM_CYCLES opcode0x5B(); // LD E, DE.LOW
    NUM_CYCLES opcode0x5C(); // LD E, HL.HIGH
    NUM_CYCLES opcode0x5D(); // LD E, HL.LOW
    NUM_CYCLES opcode0x5E(); // LD E, (HL)
    NUM_CYCLES opcode0x1E(); // LD E, NUMBER
    NUM_CYCLES opcode0x67(); // LD HL.HIGH, AF.HIGH
    NUM_CYCLES opcode0x60(); // LD HL.HIGH, BC.HIGH
    NUM_CYCLES opcode0x61(); // LD HL.HIGH, BC.LOW
    NUM_CYCLES opcode0x62(); // LD HL.HIGH, DE.HIGH
    NUM_CYCLES opcode0x63(); // LD HL.HIGH, DE.LOW
    NUM_CYCLES opcode0x64(); // LD HL.HIGH, HL.HIGH
    NUM_CYCLES opcode0x65(); // LD HL.HIGH, HL.LOW
    NUM_CYCLES opcode0x66(); // LD HL.HIGH, (HL)
    NUM_CYCLES opcode0x26(); // LD HL.HIGH, NUMBER
    NUM_CYCLES opcode0x6F(); // LD HL.LOW, AF.HIGH
    NUM_CYCLES opcode0x68(); // LD HL.LOW, BC.HIGH
    NUM_CYCLES opcode0x69(); // LD HL.LOW, BC.LOW
    NUM_CYCLES opcode0x6A(); // LD HL.LOW, DE.HIGH
    NUM_CYCLES opcode0x6B(); // LD HL.LOW, DE.LOW
    NUM_CYCLES opcode0x6C(); // LD HL.LOW, HL.HIGH
    NUM_CYCLES opcode0x6D(); // LD HL.LOW, HL.LOW
    NUM_CYCLES opcode0x6E(); // LD HL.LOW, (HL)
    NUM_CYCLES opcode0x2E(); // LD HL.LOW, NUMBER
    NUM_CYCLES opcode0x77(); // LD (HL), AF.HIGH
    NUM_CYCLES opcode0x70(); // LD (HL), BC.HIGH
    NUM_CYCLES opcode0x71(); // LD (HL), BC.LOW
    NUM_CYCLES opcode0x72(); // LD (HL), DE.HIGH
    NUM_CYCLES opcode0x73(); // LD (HL), DE.LOW
    NUM_CYCLES opcode0x74(); // LD (HL), HL.HIGH
    NUM_CYCLES opcode0x75(); // LD (HL), HL.LOW
    NUM_CYCLES opcode0x36(); // LD (HL), NUMBER
    NUM_CYCLES opcode0x0A(); // LD A, (BC)
    NUM_CYCLES opcode0x1A(); // LD A, (DE)
    NUM_CYCLES opcode0xFA(); // LD A, (NUMBER)
    NUM_CYCLES opcode0x02(); // LD (BC), A
    NUM_CYCLES opcode0x12(); // LD (DE), A
    NUM_CYCLES opcode0xEA(); // LD (NUMBER), A
    NUM_CYCLES opcode0xF0(); // LD A, (C) (0xFF00 + n)
    NUM_CYCLES opcode0xE0(); // LD (C), A (0xFF00 + n)
    NUM_CYCLES opcode0xF2(); // LD A, (C) (0xFF00 + C)
    NUM_CYCLES opcode0xE2(); // LD (C), A (0xFF00 + C)
    NUM_CYCLES opcode0x3A(); // LDD A, (HL)
    NUM_CYCLES opcode0x32(); // LDD (HL), A
    NUM_CYCLES opcode0x2A(); // LDI A, (HL)
    NUM_CYCLES opcode0x22(); // LDI (HL), A

    // 16-BIT LOAD INSTRUCTIONS
    void load16bit(REGISTER16 *reg, uint16_t value);
    NUM_CYCLES opcode0x01(); // LD BC, NUMBER
    NUM_CYCLES opcode0x11(); // LD DE, NUMBER
    NUM_CYCLES opcode0x21(); // LD HL, NUMBER
    NUM_CYCLES opcode0x31(); // LD SP, NUMBER
    NUM_CYCLES opcode0xF9(); // LD SP, HL
    NUM_CYCLES opcode0xF8(); // LD HL, SP + NUMBER
    NUM_CYCLES opcode0x08(); // LD (NUMBER), SP


    // PUSH AND POP INSTRUCTIONS
    NUM_CYCLES opcode0xF5(); // PUSH AF
    NUM_CYCLES opcode0xC5(); // PUSH BC
    NUM_CYCLES opcode0xD5(); // PUSH DE
    NUM_CYCLES opcode0xE5(); // PUSH HL
    NUM_CYCLES opcode0xF1(); // POP AF
    NUM_CYCLES opcode0xC1(); // POP BC
    NUM_CYCLES opcode0xD1(); // POP DE
    NUM_CYCLES opcode0xE1(); // POP HL


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

    // JUMP INSTRUCTIONS
    void set16bitRegister(REGISTER *reg, uint16_t value);
    NUM_CYCLES opcode0xC3(); // JP NUMBER
    NUM_CYCLES opcode0xE9(); // JP HL
    NUM_CYCLES opcode0xC2(); // JP NZ, NUMBER
    NUM_CYCLES opcode0xCA(); // JP Z, NUMBER
    NUM_CYCLES opcode0xD2(); // JP NC, NUMBER
    NUM_CYCLES opcode0xDA(); // JP C, NUMBER
    NUM_CYCLES opcode0x18(); // JP RELATIVE
    NUM_CYCLES opcode0x20(); // JR NZ, RELATIVE
    NUM_CYCLES opcode0x28(); // JR Z, RELATIVE
    NUM_CYCLES opcode0x30(); // JR NC, RELATIVE
    NUM_CYCLES opcode0x38(); // JR C, RELATIVE

    // CALL INSTRUCTIONS
    NUM_CYCLES opcode0xCD(); // CALL NUMBER
    NUM_CYCLES opcode0xC4(); // CALL NZ, NUMBER
    NUM_CYCLES opcode0xCC(); // CALL Z, NUMBER
    NUM_CYCLES opcode0xD4(); // CALL NC, NUMBER
    NUM_CYCLES opcode0xDC(); // CALL C, NUMBER

    // RETURN INSTRUCTIONS
    NUM_CYCLES opcode0xC9(); // RET
    NUM_CYCLES opcode0xC0(); // RET NZ
    NUM_CYCLES opcode0xC8(); // RET Z
    NUM_CYCLES opcode0xD0(); // RET NC
    NUM_CYCLES opcode0xD8(); // RET C
    NUM_CYCLES opcode0xD9(); // RETI
    NUM_CYCLES opcode0xC7(); // RST 0x00
    NUM_CYCLES opcode0xCF(); // RST 0x08
    NUM_CYCLES opcode0xD7(); // RST 0x10
    NUM_CYCLES opcode0xDF(); // RST 0x18
    NUM_CYCLES opcode0xE7(); // RST 0x20
    NUM_CYCLES opcode0xEF(); // RST 0x28
    NUM_CYCLES opcode0xF7(); // RST 0x30
    NUM_CYCLES opcode0xFF(); // RST 0x38



public:
    CPU(std::vector<uint8_t> rom);
    void execute();
};
