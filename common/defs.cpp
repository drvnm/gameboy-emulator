#include "defs.h"

// thank you random github page
opcodeInfo opcodeDescriptionTable[NUM_OPCODES] = {
    { "NOP", 0 }, // 0 is the amount of bytes after the opcode
	{ "LD BC, d16", 2 },
	{ "LD (BC), A", 0 },
	{ "INC BC", 0 },
	{ "INC B", 0 },
	{ "DEC B", 0 },
	{ "LD B, d8", 1 },
	{ "RLCA", 0 },
	{ "LD (a16), SP", 2 },
	{ "ADD HL, BC", 0 },
	{ "LD A, (BC)", 0 },
	{ "DEC BC", 0 },
	{ "INC C", 0 },
	{ "DEC C", 0 },
	{ "LD C, d8", 1 },
	{ "RRCA", 0 },
	{ "STOP 0", 1 },
	{ "LD DE, d16", 2 },
	{ "LD (DE), A", 0 },
	{ "INC DE", 0 },
	{ "INC D", 0 },
	{ "DEC D", 0 },
	{ "LD D, d8", 1 },
	{ "RLA", 0 },
	{ "JR r8", 1 },
	{ "ADD HL, DE", 0 },
	{ "LD A, (DE)", 0 },
	{ "DEC DE", 0 },
	{ "INC E", 0 },
	{ "DEC E", 0 },
	{ "LD E, d8", 1 },
	{ "RRA", 0 },
	{ "JR NZ, r8", 1 },
	{ "LD HL, d16", 2 },
	{ "LD (HL+), A", 0 },
	{ "INC HL", 0 },
	{ "INC H", 0 },
	{ "DEC H", 0 },
	{ "LD H, d8", 1 },
	{ "DAA", 0 },
	{ "JR Z, r8", 1 },
	{ "ADD HL, HL", 0 },
	{ "LD A, (HL+)", 0 },
	{ "DEC HL", 0 },
	{ "INC L", 0 },
	{ "DEC L", 0 },
	{ "LD L, d8", 1 },
	{ "CPL", 0 },
	{ "JR NC, r8", 1 },
	{ "LD SP, d16", 2 },
	{ "LD (HL-), A", 0 },
	{ "INC SP", 0 },
	{ "INC (HL)", 0 },
	{ "DEC (HL)", 0 },
	{ "LD (HL), d8", 1 },
	{ "SCF", 0 },
	{ "JR C, r8", 1 },
	{ "ADD HL, SP", 0 },
	{ "LD A, (HL-)", 0 },
	{ "DEC SP", 0 },
	{ "INC A", 0 },
	{ "DEC A", 0 },
	{ "LD A, d8", 1 },
	{ "CCF", 0 },
	{ "LD B, B", 0 },
	{ "LD B, C", 0 },
	{ "LD B, D", 0 },
	{ "LD B, E", 0 },
	{ "LD B, H", 0 },
	{ "LD B, L", 0 },
	{ "LD B, (HL)", 0 },
	{ "LD B, A", 0 },
	{ "LD C, B", 0 },
	{ "LD C, C", 0 },
	{ "LD C, D", 0 },
	{ "LD C, E", 0 },
	{ "LD C, H", 0 },
	{ "LD C, L", 0 },
	{ "LD C, (HL)", 0 },
	{ "LD C, A", 0 },
	{ "LD D, B", 0 },
	{ "LD D, C", 0 },
	{ "LD D, D", 0 },
	{ "LD D, E", 0 },
	{ "LD D, H", 0 },
	{ "LD D, L", 0 },
	{ "LD D, (HL)", 0 },
	{ "LD D, A", 0 },
	{ "LD E, B", 0 },
	{ "LD E, C", 0 },
	{ "LD E, D", 0 },
	{ "LD E, E", 0 },
	{ "LD E, H", 0 },
	{ "LD E, L", 0 },
	{ "LD E (HL)", 0 },
	{ "LD E, A", 0 },
	{ "LD H, B", 0 },
	{ "LD H, C", 0 },
	{ "LD H, D", 0 },
	{ "LD H, E", 0 },
	{ "LD H, H", 0 },
	{ "LD H, L", 0 },
	{ "LD H, (HL)", 0 },
	{ "LD H, A", 0 },
	{ "LD L, B", 0 },
	{ "LD L, C", 0 },
	{ "LD L, D", 0 },
	{ "LD L, E", 0 },
	{ "LD L, H", 0 },
	{ "LD L, L", 0 },
	{ "LD L, (HL)", 0 },
	{ "LD L, A", 0 },
	{ "LD (HL), B", 0 },
	{ "LD (HL), C", 0 },
	{ "LD (HL), D", 0 },
	{ "LD (HL), E", 0 },
	{ "LD (HL), H", 0 },
	{ "LD (HL), L", 0 },
	{ "HALT", 0 },
	{ "LD (HL), A", 0 },
	{ "LD A, B", 0 },
	{ "LD A, C", 0 },
	{ "LD A, D", 0 },
	{ "LD A, E", 0 },
	{ "LD A, H", 0 },
	{ "LD A, L", 0 },
	{ "LD A, (HL)", 0 },
	{ "LD A, A", 0 },
	{ "ADD A, B", 0 },
	{ "ADD A, C", 0 },
	{ "ADD A, D", 0 },
	{ "ADD A, E", 0 },
	{ "ADD A, H", 0 },
	{ "ADD A, L", 0 },
	{ "ADD A, (HL)", 0 },
	{ "ADD A, A", 0 },
	{ "ADC A, B", 0 },
	{ "ADC A, C", 0 },
	{ "ADC A, D", 0 },
	{ "ADC A, E", 0 },
	{ "ADC A, H", 0 },
	{ "ADC A, L", 0 },
	{ "ADC A, (HL)", 0 },
	{ "ADC A, A", 0 },
	{ "SUB B", 0 },
	{ "SUB C", 0 },
	{ "SUB D", 0 },
	{ "SUB E", 0 },
	{ "SUB H", 0 },
	{ "SUB L", 0 },
	{ "SUB (HL)", 0 },
	{ "SUB A", 0 },
	{ "SBC A, B", 0 },
	{ "SBC A, C", 0 },
	{ "SBC A, D", 0 },
	{ "SBC A, E", 0 },
	{ "SBC A, H", 0 },
	{ "SBC A, L", 0 },
	{ "SBC A, (HL)", 0 },
	{ "SBC A, A", 0 },
	{ "AND B", 0 },
	{ "AND C", 0 },
	{ "AND D", 0 },
	{ "AND E", 0 },
	{ "AND H", 0 },
	{ "AND L", 0 },
	{ "AND (HL)", 0 },
	{ "AND A", 0 },
	{ "XOR B", 0 },
	{ "XOR C", 0 },
	{ "XOR D", 0 },
	{ "XOR E", 0 },
	{ "XOR H", 0 },
	{ "XOR L", 0 },
	{ "XOR (HL)", 0 },
	{ "XOR A", 0 },
	{ "OR B", 0 },
	{ "OR C", 0 },
	{ "OR D", 0 },
	{ "OR E", 0 },
	{ "OR H", 0 },
	{ "OR L", 0 },
	{ "OR (HL)", 0 },
	{ "OR A", 0 },
	{ "CP B", 0 },
	{ "CP C", 0 },
	{ "CP D", 0 },
	{ "CP E", 0 },
	{ "CP H", 0 },
	{ "CP L", 0 },
	{ "CP (HL)", 0 },
	{ "CP A", 0 },
	{ "RET NZ", 0 },
	{ "POP BC", 0 },
	{ "JP NZ, a16", 2 },
	{ "JP a16", 2 },
	{ "CALL NZ, a16", 2 },
	{ "PUSH BC", 0 },
	{ "ADD A, d8", 1 },
	{ "RST 00H", 0 },
	{ "RET Z", 0 },
	{ "RET", 0 },
	{ "JP Z, a16", 2 },
	{ "PREFIX CB", 1 },
	{ "CALL Z, a16", 2 },
	{ "CALL a16", 2 },
	{ "ADC A, d8", 1 },
	{ "RST 08H", 0 },
	{ "RET NC", 0 },
	{ "POP DE", 0 },
	{ "JP NC, a16", 2 },
	{ "INVALID", 0 },
	{ "CALL NC, a16", 2 },
	{ "PUSH DE", 0 },
	{ "SUB d8", 1 },
	{ "RST 10H", 0 },
	{ "RET C", 0 },
	{ "RETI", 0 },
	{ "JP C, a16", 2 },
	{ "INVALID", 0 },
	{ "CALL C, a16", 2 },
	{ "INVALID", 0 },
	{ "SBC A, d8", 1 },
	{ "RST 18H", 0 },
	{ "LDH (a8), A", 1 },
	{ "POP HL", 0 },
	{ "LD (C), A", 0 },
	{ "INVALID", 0 },
	{ "INVALID", 0 },
	{ "PUSH HL", 0 },
	{ "AND d8", 1 },
	{ "RST 20H", 0 },
	{ "ADD SP, r8", 1 },
	{ "JP HL", 0 },
	{ "LD (a16), A", 2 },
	{ "INVALID", 0 },
	{ "INVALID", 0 },
	{ "INVALID", 0 },
	{ "XOR d8", 1 },
	{ "RST 28H", 0 },
	{ "LDH A, (a8)", 1 },
	{ "POP AF", 0 },
	{ "LD A, (C)", 0 },
	{ "DI", 0 },
	{ "INVALID", 0 },
	{ "PUSH AF", 0 },
	{ "OR d8", 1 },
	{ "RST 30H", 0 },
	{ "LD HL, SP+r8", 1 }, 
	{ "LD SP, HL", 0 },
	{ "LD A, (a16)", 2 },
	{ "EI", 0 },
	{ "INVALID", 0 },
	{ "INVALID", 0 },
	{ "CP d8", 1 },
	{ "RST 38H", 0 }
};
