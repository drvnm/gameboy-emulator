#pragma once

#include <vector>
#include <map>

#include "registers.h"
#include "../memory/memory.h"
#include "../debugger/debugger.h"


// emulates the CPU of the gameboy (the sharp LR35902)
class CPU
{
public:
    // display stuff
    Memory *memory;
    Debugger *debugger;
    short (CPU::*opcodes[0xFF + 1])();         // array of function pointers to the opcodes
    short (CPU::*extendedOpcodes[0xFF + 1])(); // array of function pointers to the cb opcodes
    Registers registers;                       // 8-bit registers
    void setupOpcodes();                       // sets up the opcodes

    uint8_t executeInstruction(OPCODE instruction); // fetches and executes the instruction
    void requestInterrupt(uint8_t interrupt);       // requests an interrupt
    void handleInterrupts();                        // handles interrupts
    void serviceInterrupt(uint8_t interrupt);       // services an interrupt

    // stack operations
    void push(uint16_t value);
    uint16_t pop();

    // helper functions
    uint16_t load16BitFromPC();
    void reset();

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

    void add16bit(REGISTER16 *reg, uint16_t value);
    NUM_CYCLES opcode0x09(); // ADD HL, BC
    NUM_CYCLES opcode0x19(); // ADD HL, DE
    NUM_CYCLES opcode0x29(); // ADD HL, HL
    NUM_CYCLES opcode0x39(); // ADD HL, SP



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
    void inc16bit(REGISTER16 *reg);
    NUM_CYCLES opcode0x03(); // INC BC
    NUM_CYCLES opcode0x13(); // INC DE
    NUM_CYCLES opcode0x23(); // INC HL
    NUM_CYCLES opcode0x33(); // INC SP
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
    void dec16bit(REGISTER16 *reg);
    NUM_CYCLES opcode0x0B(); // DEC BC
    NUM_CYCLES opcode0x1B(); // DEC DE
    NUM_CYCLES opcode0x2B(); // DEC HL
    NUM_CYCLES opcode0x3B(); // DEC SP
    // DAA INSTRUCTIONS
    NUM_CYCLES opcode0x27(); // DAA
    // CPL INSTRUCTIONS
    NUM_CYCLES opcode0x2F(); // CPL

    // CONTROL INSTRUCTIONS
    NUM_CYCLES opcode0x3F(); // CCF (CY = CY XOR 1)
    NUM_CYCLES opcode0x37(); // SCF (CY = 1)
    NUM_CYCLES opcode0x76(); // HALT
    NUM_CYCLES opcode0x10(); // STOP
    NUM_CYCLES opcode0xF3(); // DI
    NUM_CYCLES opcode0xFB(); // EI

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

    // ROTATE INSTRUCTIONS
    void rotateLeft(REGISTER *reg, bool throughCarry);
    void rotateRight(REGISTER *reg, bool throughCarry);
    NUM_CYCLES opcode0x07(); // RLCA
    NUM_CYCLES opcode0x17(); // RLA
    NUM_CYCLES opcode0x0F(); // RRCA
    NUM_CYCLES opcode0x1F(); // RRA

    // ROTATE WITH EXTENDED INSTRUCTIONS
    void rlc8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x07(); // RLC AF.HIGH
    NUM_CYCLES extendedOpcode0x00(); // RLC BC.HIGH
    NUM_CYCLES extendedOpcode0x01(); // RLC BC.LOW
    NUM_CYCLES extendedOpcode0x02(); // RLC DE.HIGH
    NUM_CYCLES extendedOpcode0x03(); // RLC DE.LOW
    NUM_CYCLES extendedOpcode0x04(); // RLC HL.HIGH
    NUM_CYCLES extendedOpcode0x05(); // RLC HL.LOW
    NUM_CYCLES extendedOpcode0x06(); // RLC (HL)

    void rrc8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x0F(); // RRC AF.HIGH
    NUM_CYCLES extendedOpcode0x08(); // RRC BC.HIGH
    NUM_CYCLES extendedOpcode0x09(); // RRC BC.LOW
    NUM_CYCLES extendedOpcode0x0A(); // RRC DE.HIGH
    NUM_CYCLES extendedOpcode0x0B(); // RRC DE.LOW
    NUM_CYCLES extendedOpcode0x0C(); // RRC HL.HIGH
    NUM_CYCLES extendedOpcode0x0D(); // RRC HL.LOW
    NUM_CYCLES extendedOpcode0x0E(); // RRC (HL)

    void rl8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x17(); // RL AF.HIGH
    NUM_CYCLES extendedOpcode0x10(); // RL BC.HIGH
    NUM_CYCLES extendedOpcode0x11(); // RL BC.LOW
    NUM_CYCLES extendedOpcode0x12(); // RL DE.HIGH
    NUM_CYCLES extendedOpcode0x13(); // RL DE.LOW
    NUM_CYCLES extendedOpcode0x14(); // RL HL.HIGH
    NUM_CYCLES extendedOpcode0x15(); // RL HL.LOW
    NUM_CYCLES extendedOpcode0x16(); // RL (HL)

    void rr8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x1F(); // RR AF.HIGH
    NUM_CYCLES extendedOpcode0x18(); // RR BC.HIGH
    NUM_CYCLES extendedOpcode0x19(); // RR BC.LOW
    NUM_CYCLES extendedOpcode0x1A(); // RR DE.HIGH
    NUM_CYCLES extendedOpcode0x1B(); // RR DE.LOW
    NUM_CYCLES extendedOpcode0x1C(); // RR HL.HIGH
    NUM_CYCLES extendedOpcode0x1D(); // RR HL.LOW
    NUM_CYCLES extendedOpcode0x1E(); // RR (HL)

    // SHIFT INSTRUCTIONS
    void sla8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x27(); // SLA AF.HIGH
    NUM_CYCLES extendedOpcode0x20(); // SLA BC.HIGH
    NUM_CYCLES extendedOpcode0x21(); // SLA BC.LOW
    NUM_CYCLES extendedOpcode0x22(); // SLA DE.HIGH
    NUM_CYCLES extendedOpcode0x23(); // SLA DE.LOW
    NUM_CYCLES extendedOpcode0x24(); // SLA HL.HIGH
    NUM_CYCLES extendedOpcode0x25(); // SLA HL.LOW
    NUM_CYCLES extendedOpcode0x26(); // SLA (HL)

    void sra8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x2F(); // SRA AF.HIGH
    NUM_CYCLES extendedOpcode0x28(); // SRA BC.HIGH
    NUM_CYCLES extendedOpcode0x29(); // SRA BC.LOW
    NUM_CYCLES extendedOpcode0x2A(); // SRA DE.HIGH
    NUM_CYCLES extendedOpcode0x2B(); // SRA DE.LOW
    NUM_CYCLES extendedOpcode0x2C(); // SRA HL.HIGH
    NUM_CYCLES extendedOpcode0x2D(); // SRA HL.LOW
    NUM_CYCLES extendedOpcode0x2E(); // SRA (HL)

    void srl8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x3F(); // SRL AF.HIGH
    NUM_CYCLES extendedOpcode0x30(); // SRL BC.HIGH
    NUM_CYCLES extendedOpcode0x31(); // SRL BC.LOW
    NUM_CYCLES extendedOpcode0x32(); // SRL DE.HIGH
    NUM_CYCLES extendedOpcode0x33(); // SRL DE.LOW
    NUM_CYCLES extendedOpcode0x34(); // SRL HL.HIGH
    NUM_CYCLES extendedOpcode0x35(); // SRL HL.LOW
    NUM_CYCLES extendedOpcode0x36(); // SRL (HL)

    // SWAP INSTRUCTIONS
    void swap8bit(REGISTER *reg);
    NUM_CYCLES extendedOpcode0x37(); // SWAP AF.HIGH
    NUM_CYCLES extendedOpcode0x38(); // SWAP BC.HIGH
    NUM_CYCLES extendedOpcode0x39(); // SWAP BC.LOW
    NUM_CYCLES extendedOpcode0x3A(); // SWAP DE.HIGH
    NUM_CYCLES extendedOpcode0x3B(); // SWAP DE.LOW
    NUM_CYCLES extendedOpcode0x3C(); // SWAP HL.HIGH
    NUM_CYCLES extendedOpcode0x3D(); // SWAP HL.LOW
    NUM_CYCLES extendedOpcode0x3E(); // SWAP (HL)

    // SINGLE BIT INSTRUCTIONS
    void bit(REGISTER *reg, uint8_t bit);
    NUM_CYCLES extendedOpcode0x47(); // BIT 0, AF.HIGH
    NUM_CYCLES extendedOpcode0x40(); // BIT 0, BC.HIGH
    NUM_CYCLES extendedOpcode0x41(); // BIT 0, BC.LOW
    NUM_CYCLES extendedOpcode0x42(); // BIT 0, DE.HIGH
    NUM_CYCLES extendedOpcode0x43(); // BIT 0, DE.LOW
    NUM_CYCLES extendedOpcode0x44(); // BIT 0, HL.HIGH
    NUM_CYCLES extendedOpcode0x45(); // BIT 0, HL.LOW
    NUM_CYCLES extendedOpcode0x46(); // BIT 0, (HL)
    NUM_CYCLES extendedOpcode0x4F(); // BIT 1, AF.HIGH
    NUM_CYCLES extendedOpcode0x48(); // BIT 1, BC.HIGH
    NUM_CYCLES extendedOpcode0x49(); // BIT 1, BC.LOW
    NUM_CYCLES extendedOpcode0x4A(); // BIT 1, DE.HIGH
    NUM_CYCLES extendedOpcode0x4B(); // BIT 1, DE.LOW
    NUM_CYCLES extendedOpcode0x4C(); // BIT 1, HL.HIGH
    NUM_CYCLES extendedOpcode0x4D(); // BIT 1, HL.LOW
    NUM_CYCLES extendedOpcode0x4E(); // BIT 1, (HL)
    NUM_CYCLES extendedOpcode0x57(); // BIT 2, AF.HIGH
    NUM_CYCLES extendedOpcode0x50(); // BIT 2, BC.HIGH
    NUM_CYCLES extendedOpcode0x51(); // BIT 2, BC.LOW
    NUM_CYCLES extendedOpcode0x52(); // BIT 2, DE.HIGH
    NUM_CYCLES extendedOpcode0x53(); // BIT 2, DE.LOW
    NUM_CYCLES extendedOpcode0x54(); // BIT 2, HL.HIGH
    NUM_CYCLES extendedOpcode0x55(); // BIT 2, HL.LOW
    NUM_CYCLES extendedOpcode0x56(); // BIT 2, (HL)
    NUM_CYCLES extendedOpcode0x5F(); // BIT 3, AF.HIGH
    NUM_CYCLES extendedOpcode0x58(); // BIT 3, BC.HIGH
    NUM_CYCLES extendedOpcode0x59(); // BIT 3, BC.LOW
    NUM_CYCLES extendedOpcode0x5A(); // BIT 3, DE.HIGH
    NUM_CYCLES extendedOpcode0x5B(); // BIT 3, DE.LOW
    NUM_CYCLES extendedOpcode0x5C(); // BIT 3, HL.HIGH
    NUM_CYCLES extendedOpcode0x5D(); // BIT 3, HL.LOW
    NUM_CYCLES extendedOpcode0x5E(); // BIT 3, (HL)
    NUM_CYCLES extendedOpcode0x67(); // BIT 4, AF.HIGH
    NUM_CYCLES extendedOpcode0x60(); // BIT 4, BC.HIGH
    NUM_CYCLES extendedOpcode0x61(); // BIT 4, BC.LOW
    NUM_CYCLES extendedOpcode0x62(); // BIT 4, DE.HIGH
    NUM_CYCLES extendedOpcode0x63(); // BIT 4, DE.LOW
    NUM_CYCLES extendedOpcode0x64(); // BIT 4, HL.HIGH
    NUM_CYCLES extendedOpcode0x65(); // BIT 4, HL.LOW
    NUM_CYCLES extendedOpcode0x66(); // BIT 4, (HL)
    NUM_CYCLES extendedOpcode0x6F(); // BIT 5, AF.HIGH
    NUM_CYCLES extendedOpcode0x68(); // BIT 5, BC.HIGH
    NUM_CYCLES extendedOpcode0x69(); // BIT 5, BC.LOW
    NUM_CYCLES extendedOpcode0x6A(); // BIT 5, DE.HIGH
    NUM_CYCLES extendedOpcode0x6B(); // BIT 5, DE.LOW
    NUM_CYCLES extendedOpcode0x6C(); // BIT 5, HL.HIGH
    NUM_CYCLES extendedOpcode0x6D(); // BIT 5, HL.LOW
    NUM_CYCLES extendedOpcode0x6E(); // BIT 5, (HL)
    NUM_CYCLES extendedOpcode0x77(); // BIT 6, AF.HIGH
    NUM_CYCLES extendedOpcode0x70(); // BIT 6, BC.HIGH
    NUM_CYCLES extendedOpcode0x71(); // BIT 6, BC.LOW
    NUM_CYCLES extendedOpcode0x72(); // BIT 6, DE.HIGH
    NUM_CYCLES extendedOpcode0x73(); // BIT 6, DE.LOW
    NUM_CYCLES extendedOpcode0x74(); // BIT 6, HL.HIGH
    NUM_CYCLES extendedOpcode0x75(); // BIT 6, HL.LOW
    NUM_CYCLES extendedOpcode0x76(); // BIT 6, (HL)
    NUM_CYCLES extendedOpcode0x7F(); // BIT 7, AF.HIGH
    NUM_CYCLES extendedOpcode0x78(); // BIT 7, BC.HIGH
    NUM_CYCLES extendedOpcode0x79(); // BIT 7, BC.LOW
    NUM_CYCLES extendedOpcode0x7A(); // BIT 7, DE.HIGH
    NUM_CYCLES extendedOpcode0x7B(); // BIT 7, DE.LOW
    NUM_CYCLES extendedOpcode0x7C(); // BIT 7, HL.HIGH
    NUM_CYCLES extendedOpcode0x7D(); // BIT 7, HL.LOW
    NUM_CYCLES extendedOpcode0x7E(); // BIT 7, (HL)

    // SET INSTRUCTIONS
    void set(REGISTER *reg, uint8_t bit);
    NUM_CYCLES extendedOpcode0xC7(); // SET 0, AF.HIGH
    NUM_CYCLES extendedOpcode0xC0(); // SET 0, BC.HIGH
    NUM_CYCLES extendedOpcode0xC1(); // SET 0, BC.LOW
    NUM_CYCLES extendedOpcode0xC2(); // SET 0, DE.HIGH
    NUM_CYCLES extendedOpcode0xC3(); // SET 0, DE.LOW
    NUM_CYCLES extendedOpcode0xC4(); // SET 0, HL.HIGH
    NUM_CYCLES extendedOpcode0xC5(); // SET 0, HL.LOW
    NUM_CYCLES extendedOpcode0xC6(); // SET 0, (HL)
    NUM_CYCLES extendedOpcode0xCF(); // SET 1, AF.HIGH
    NUM_CYCLES extendedOpcode0xC8(); // SET 1, BC.HIGH
    NUM_CYCLES extendedOpcode0xC9(); // SET 1, BC.LOW
    NUM_CYCLES extendedOpcode0xCA(); // SET 1, DE.HIGH
    NUM_CYCLES extendedOpcode0xCB(); // SET 1, DE.LOW
    NUM_CYCLES extendedOpcode0xCC(); // SET 1, HL.HIGH
    NUM_CYCLES extendedOpcode0xCD(); // SET 1, HL.LOW
    NUM_CYCLES extendedOpcode0xCE(); // SET 1, (HL)
    NUM_CYCLES extendedOpcode0xD7(); // SET 2, AF.HIGH
    NUM_CYCLES extendedOpcode0xD0(); // SET 2, BC.HIGH
    NUM_CYCLES extendedOpcode0xD1(); // SET 2, BC.LOW
    NUM_CYCLES extendedOpcode0xD2(); // SET 2, DE.HIGH
    NUM_CYCLES extendedOpcode0xD3(); // SET 2, DE.LOW
    NUM_CYCLES extendedOpcode0xD4(); // SET 2, HL.HIGH
    NUM_CYCLES extendedOpcode0xD5(); // SET 2, HL.LOW
    NUM_CYCLES extendedOpcode0xD6(); // SET 2, (HL)
    NUM_CYCLES extendedOpcode0xDF(); // SET 3, AF.HIGH
    NUM_CYCLES extendedOpcode0xD8(); // SET 3, BC.HIGH
    NUM_CYCLES extendedOpcode0xD9(); // SET 3, BC.LOW
    NUM_CYCLES extendedOpcode0xDA(); // SET 3, DE.HIGH
    NUM_CYCLES extendedOpcode0xDB(); // SET 3, DE.LOW
    NUM_CYCLES extendedOpcode0xDC(); // SET 3, HL.HIGH
    NUM_CYCLES extendedOpcode0xDD(); // SET 3, HL.LOW
    NUM_CYCLES extendedOpcode0xDE(); // SET 3, (HL)
    NUM_CYCLES extendedOpcode0xE7(); // SET 4, AF.HIGH
    NUM_CYCLES extendedOpcode0xE0(); // SET 4, BC.HIGH
    NUM_CYCLES extendedOpcode0xE1(); // SET 4, BC.LOW
    NUM_CYCLES extendedOpcode0xE2(); // SET 4, DE.HIGH
    NUM_CYCLES extendedOpcode0xE3(); // SET 4, DE.LOW
    NUM_CYCLES extendedOpcode0xE4(); // SET 4, HL.HIGH
    NUM_CYCLES extendedOpcode0xE5(); // SET 4, HL.LOW
    NUM_CYCLES extendedOpcode0xE6(); // SET 4, (HL)
    NUM_CYCLES extendedOpcode0xEF(); // SET 5, AF.HIGH
    NUM_CYCLES extendedOpcode0xE8(); // SET 5, BC.HIGH
    NUM_CYCLES extendedOpcode0xE9(); // SET 5, BC.LOW
    NUM_CYCLES extendedOpcode0xEA(); // SET 5, DE.HIGH
    NUM_CYCLES extendedOpcode0xEB(); // SET 5, DE.LOW
    NUM_CYCLES extendedOpcode0xEC(); // SET 5, HL.HIGH
    NUM_CYCLES extendedOpcode0xED(); // SET 5, HL.LOW
    NUM_CYCLES extendedOpcode0xEE(); // SET 5, (HL)
    NUM_CYCLES extendedOpcode0xF7(); // SET 6, AF.HIGH
    NUM_CYCLES extendedOpcode0xF0(); // SET 6, BC.HIGH
    NUM_CYCLES extendedOpcode0xF1(); // SET 6, BC.LOW
    NUM_CYCLES extendedOpcode0xF2(); // SET 6, DE.HIGH
    NUM_CYCLES extendedOpcode0xF3(); // SET 6, DE.LOW
    NUM_CYCLES extendedOpcode0xF4(); // SET 6, HL.HIGH
    NUM_CYCLES extendedOpcode0xF5(); // SET 6, HL.LOW
    NUM_CYCLES extendedOpcode0xF6(); // SET 6, (HL)
    NUM_CYCLES extendedOpcode0xFF(); // SET 7, AF.HIGH
    NUM_CYCLES extendedOpcode0xF8(); // SET 7, BC.HIGH
    NUM_CYCLES extendedOpcode0xF9(); // SET 7, BC.LOW
    NUM_CYCLES extendedOpcode0xFA(); // SET 7, DE.HIGH
    NUM_CYCLES extendedOpcode0xFB(); // SET 7, DE.LOW
    NUM_CYCLES extendedOpcode0xFC(); // SET 7, HL.HIGH
    NUM_CYCLES extendedOpcode0xFD(); // SET 7, HL.LOW
    NUM_CYCLES extendedOpcode0xFE(); // SET 7, (HL)

    // RESET INSTRUCTIONS
    void res(REGISTER *reg, uint8_t bit);
    NUM_CYCLES extendedOpcode0x87(); // RES 0, AF.HIGH
    NUM_CYCLES extendedOpcode0x80(); // RES 0, BC.HIGH
    NUM_CYCLES extendedOpcode0x81(); // RES 0, BC.LOW
    NUM_CYCLES extendedOpcode0x82(); // RES 0, DE.HIGH
    NUM_CYCLES extendedOpcode0x83(); // RES 0, DE.LOW
    NUM_CYCLES extendedOpcode0x84(); // RES 0, HL.HIGH
    NUM_CYCLES extendedOpcode0x85(); // RES 0, HL.LOW
    NUM_CYCLES extendedOpcode0x86(); // RES 0, (HL)
    NUM_CYCLES extendedOpcode0x8F(); // RES 1, AF.HIGH
    NUM_CYCLES extendedOpcode0x88(); // RES 1, BC.HIGH
    NUM_CYCLES extendedOpcode0x89(); // RES 1, BC.LOW
    NUM_CYCLES extendedOpcode0x8A(); // RES 1, DE.HIGH
    NUM_CYCLES extendedOpcode0x8B(); // RES 1, DE.LOW
    NUM_CYCLES extendedOpcode0x8C(); // RES 1, HL.HIGH
    NUM_CYCLES extendedOpcode0x8D(); // RES 1, HL.LOW
    NUM_CYCLES extendedOpcode0x8E(); // RES 1, (HL)
    NUM_CYCLES extendedOpcode0x97(); // RES 2, AF.HIGH
    NUM_CYCLES extendedOpcode0x90(); // RES 2, BC.HIGH
    NUM_CYCLES extendedOpcode0x91(); // RES 2, BC.LOW
    NUM_CYCLES extendedOpcode0x92(); // RES 2, DE.HIGH
    NUM_CYCLES extendedOpcode0x93(); // RES 2, DE.LOW
    NUM_CYCLES extendedOpcode0x94(); // RES 2, HL.HIGH
    NUM_CYCLES extendedOpcode0x95(); // RES 2, HL.LOW
    NUM_CYCLES extendedOpcode0x96(); // RES 2, (HL)
    NUM_CYCLES extendedOpcode0x9F(); // RES 3, AF.HIGH
    NUM_CYCLES extendedOpcode0x98(); // RES 3, BC.HIGH
    NUM_CYCLES extendedOpcode0x99(); // RES 3, BC.LOW
    NUM_CYCLES extendedOpcode0x9A(); // RES 3, DE.HIGH
    NUM_CYCLES extendedOpcode0x9B(); // RES 3, DE.LOW
    NUM_CYCLES extendedOpcode0x9C(); // RES 3, HL.HIGH
    NUM_CYCLES extendedOpcode0x9D(); // RES 3, HL.LOW
    NUM_CYCLES extendedOpcode0x9E(); // RES 3, (HL)
    NUM_CYCLES extendedOpcode0xA7(); // RES 4, AF.HIGH
    NUM_CYCLES extendedOpcode0xA0(); // RES 4, BC.HIGH
    NUM_CYCLES extendedOpcode0xA1(); // RES 4, BC.LOW
    NUM_CYCLES extendedOpcode0xA2(); // RES 4, DE.HIGH
    NUM_CYCLES extendedOpcode0xA3(); // RES 4, DE.LOW
    NUM_CYCLES extendedOpcode0xA4(); // RES 4, HL.HIGH
    NUM_CYCLES extendedOpcode0xA5(); // RES 4, HL.LOW
    NUM_CYCLES extendedOpcode0xA6(); // RES 4, (HL)
    NUM_CYCLES extendedOpcode0xAF(); // RES 5, AF.HIGH
    NUM_CYCLES extendedOpcode0xA8(); // RES 5, BC.HIGH
    NUM_CYCLES extendedOpcode0xA9(); // RES 5, BC.LOW
    NUM_CYCLES extendedOpcode0xAA(); // RES 5, DE.HIGH
    NUM_CYCLES extendedOpcode0xAB(); // RES 5, DE.LOW
    NUM_CYCLES extendedOpcode0xAC(); // RES 5, HL.HIGH
    NUM_CYCLES extendedOpcode0xAD(); // RES 5, HL.LOW
    NUM_CYCLES extendedOpcode0xAE(); // RES 5, (HL)
    NUM_CYCLES extendedOpcode0xB7(); // RES 6, AF.HIGH
    NUM_CYCLES extendedOpcode0xB0(); // RES 6, BC.HIGH
    NUM_CYCLES extendedOpcode0xB1(); // RES 6, BC.LOW
    NUM_CYCLES extendedOpcode0xB2(); // RES 6, DE.HIGH
    NUM_CYCLES extendedOpcode0xB3(); // RES 6, DE.LOW
    NUM_CYCLES extendedOpcode0xB4(); // RES 6, HL.HIGH
    NUM_CYCLES extendedOpcode0xB5(); // RES 6, HL.LOW
    NUM_CYCLES extendedOpcode0xB6(); // RES 6, (HL)
    NUM_CYCLES extendedOpcode0xBF(); // RES 7, AF.HIGH
    NUM_CYCLES extendedOpcode0xB8(); // RES 7, BC.HIGH
    NUM_CYCLES extendedOpcode0xB9(); // RES 7, BC.LOW
    NUM_CYCLES extendedOpcode0xBA(); // RES 7, DE.HIGH
    NUM_CYCLES extendedOpcode0xBB(); // RES 7, DE.LOW
    NUM_CYCLES extendedOpcode0xBC(); // RES 7, HL.HIGH
    NUM_CYCLES extendedOpcode0xBD(); // RES 7, HL.LOW
    NUM_CYCLES extendedOpcode0xBE(); // RES 7, (HL)

    CPU(Memory *memory, Debugger *debugger);
    uint8_t step();
};
