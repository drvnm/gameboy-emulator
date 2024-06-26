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

opcodeInfo extendedOpcodeDescriptionTable[NUM_OPCODES] = {
	{ "RLC B", 0 },
	{ "RLC C", 0 },
	{ "RLC D", 0 },
	{ "RLC E", 0 },
	{ "RLC H", 0 },
	{ "RLC L", 0 },
	{ "RLC (HL)", 0 },
	{ "RLC A", 0 },
	{ "RRC B", 0 },
	{ "RRC C", 0 },
	{ "RRC D", 0 },
	{ "RRC E", 0 },
	{ "RRC H", 0 },
	{ "RRC L", 0 },
	{ "RRC (HL)", 0 },
	{ "RRC A", 0 },
	{ "RL B", 0 },
	{ "RL C", 0 },
	{ "RL D", 0 },
	{ "RL E", 0 },
	{ "RL H", 0 },
	{ "RL L", 0 },
	{ "RL (HL)", 0 },
	{ "RL A", 0 },
	{ "RR B", 0 },
	{ "RR C", 0 },
	{ "RR D", 0 },
	{ "RR E", 0 },
	{ "RR H", 0 },
	{ "RR L", 0 },
	{ "RR (HL)", 0 },
	{ "RR A", 0 },
	{ "SLA B", 0 },
	{ "SLA C", 0 },
	{ "SLA D", 0 },
	{ "SLA E", 0 },
	{ "SLA H", 0 },
	{ "SLA L", 0 },
	{ "SLA (HL)", 0 },
	{ "SLA A", 0 },
	{ "SRA B", 0 },
	{ "SRA C", 0 },
	{ "SRA D", 0 },
	{ "SRA E", 0 },
	{ "SRA H", 0 },
	{ "SRA L", 0 },
	{ "SRA (HL)", 0 },
	{ "SRA A", 0 },
	{ "SWAP B", 0 },
	{ "SWAP C", 0 },
	{ "SWAP D", 0 },
	{ "SWAP E", 0 },
	{ "SWAP H", 0 },
	{ "SWAP L", 0 },
	{ "SWAP (HL)", 0 },
	{ "SWAP A", 0 },
	{ "SRL B", 0 },
	{ "SRL C", 0 },
	{ "SRL D", 0 },
	{ "SRL E", 0 },
	{ "SRL H", 0 },
	{ "SRL L", 0 },
	{ "SRL (HL)", 0 },
	{ "SRL A", 0 },
	{ "BIT 0, B", 0 },
	{ "BIT 0, C", 0 },
	{ "BIT 0, D", 0 },
	{ "BIT 0, E", 0 },
	{ "BIT 0, H", 0 },
	{ "BIT 0, L", 0 },
	{ "BIT 0, (HL)", 0 },
	{ "BIT 0, A", 0 },
	{ "BIT 1, B", 0 },
	{ "BIT 1, C", 0 },
	{ "BIT 1, D", 0 },
	{ "BIT 1, E", 0 },
	{ "BIT 1, H", 0 },
	{ "BIT 1, L", 0 },
	{ "BIT 1, (HL)", 0 },
	{ "BIT 1, A", 0 },
	{ "BIT 2, B", 0 },
	{ "BIT 2, C", 0 },
	{ "BIT 2, D", 0 },
	{ "BIT 2, E", 0 },
	{ "BIT 2, H", 0 },
	{ "BIT 2, L", 0 },
	{ "BIT 2, (HL)", 0 },
	{ "BIT 2, A", 0 },
	{ "BIT 3, B", 0 },
	{ "BIT 3, C", 0 },
	{ "BIT 3, D", 0 },
	{ "BIT 3, E", 0 },
	{ "BIT 3, H", 0 },
	{ "BIT 3, L", 0 },
	{ "BIT 3, (HL)", 0 },
	{ "BIT 3, A", 0 },
	{ "BIT 4, B", 0 },
	{ "BIT 4, C", 0 },
	{ "BIT 4, D", 0 },
	{ "BIT 4, E", 0 },
	{ "BIT 4, H", 0 },
	{ "BIT 4, L", 0 },
	{ "BIT 4, (HL)", 0 },
	{ "BIT 4, A", 0 },
	{ "BIT 5, B", 0 },
	{ "BIT 5, C", 0 },
	{ "BIT 5, D", 0 },
	{ "BIT 5, E", 0 },
	{ "BIT 5, H", 0 },
	{ "BIT 5, L", 0 },
	{ "BIT 5, (HL)", 0 },
	{ "BIT 5, A", 0 },
	{ "BIT 6, B", 0 },
	{ "BIT 6, C", 0 },
	{ "BIT 6, D", 0 },
	{ "BIT 6, E", 0 },
	{ "BIT 6, H", 0 },
	{ "BIT 6, L", 0 },
	{ "BIT 6, (HL)", 0 },
	{ "BIT 6, A", 0 },
	{ "BIT 7, B", 0 },
	{ "BIT 7, C", 0 },
	{ "BIT 7, D", 0 },
	{ "BIT 7, E", 0 },
	{ "BIT 7, H", 0 },
	{ "BIT 7, L", 0 },
	{ "BIT 7, (HL)", 0 },
	{ "BIT 7, A", 0 },
	{ "RES 0, B", 0 },
	{ "RES 0, C", 0 },
	{ "RES 0, D", 0 },
	{ "RES 0, E", 0 },
	{ "RES 0, H", 0 },
	{ "RES 0, L", 0 },
	{ "RES 0, (HL)", 0 },
	{ "RES 0, A", 0 },
	{ "RES 1, B", 0 },
	{ "RES 1, C", 0 },
	{ "RES 1, D", 0 },
	{ "RES 1, E", 0 },
	{ "RES 1, H", 0 },
	{ "RES 1, L", 0 },
	{ "RES 1, (HL)", 0 },
	{ "RES 1, A", 0 },
	{ "RES 2, B", 0 },
	{ "RES 2, C", 0 },
	{ "RES 2, D", 0 },
	{ "RES 2, E", 0 },
	{ "RES 2, H", 0 },
	{ "RES 2, L", 0 },
	{ "RES 2, (HL)", 0 },
	{ "RES 2, A", 0 },
	{ "RES 3, B", 0 },
	{ "RES 3, C", 0 },
	{ "RES 3, D", 0 },
	{ "RES 3, E", 0 },
	{ "RES 3, H", 0 },
	{ "RES 3, L", 0 },
	{ "RES 3, (HL)", 0 },
	{ "RES 3, A", 0 },
	{ "RES 4, B", 0 },
	{ "RES 4, C", 0 },
	{ "RES 4, D", 0 },
	{ "RES 4, E", 0 },
	{ "RES 4, H", 0 },
	{ "RES 4, L", 0 },
	{ "RES 4, (HL)", 0 },
	{ "RES 4, A", 0 },
	{ "RES 5, B", 0 },
	{ "RES 5, C", 0 },
	{ "RES 5, D", 0 },
	{ "RES 5, E", 0 },
	{ "RES 5, H", 0 },
	{ "RES 5, L", 0 },
	{ "RES 5, (HL)", 0 },
	{ "RES 5, A", 0 },
	{ "RES 6, B", 0 },
	{ "RES 6, C", 0 },
	{ "RES 6, D", 0 },
	{ "RES 6, E", 0 },
	{ "RES 6, H", 0 },
	{ "RES 6, L", 0 },
	{ "RES 6, (HL)", 0 },
	{ "RES 6, A", 0 },
	{ "RES 7, B", 0 },
	{ "RES 7, C", 0 },
	{ "RES 7, D", 0 },
	{ "RES 7, E", 0 },
	{ "RES 7, H", 0 },
	{ "RES 7, L", 0 },
	{ "RES 7, (HL)", 0 },
	{ "RES 7, A", 0 },
	{ "SET 0, B", 0 },
	{ "SET 0, C", 0 },
	{ "SET 0, D", 0 },
	{ "SET 0, E", 0 },
	{ "SET 0, H", 0 },
	{ "SET 0, L", 0 },
	{ "SET 0, (HL)", 0 },
	{ "SET 0, A", 0 },
	{ "SET 1, B", 0 },
	{ "SET 1, C", 0 },
	{ "SET 1, D", 0 },
	{ "SET 1, E", 0 },
	{ "SET 1, H", 0 },
	{ "SET 1, L", 0 },
	{ "SET 1, (HL)", 0 },
	{ "SET 1, A", 0 },
	{ "SET 2, B", 0 },
	{ "SET 2, C", 0 },
	{ "SET 2, D", 0 },
	{ "SET 2, E", 0 },
	{ "SET 2, H", 0 },
	{ "SET 2, L", 0 },
	{ "SET 2, (HL)", 0 },
	{ "SET 2, A", 0 },
	{ "SET 3, B", 0 },
	{ "SET 3, C", 0 },
	{ "SET 3, D", 0 },
	{ "SET 3, E", 0 },
	{ "SET 3, H", 0 },
	{ "SET 3, L", 0 },
	{ "SET 3, (HL)", 0 },
	{ "SET 3, A", 0 },
	{ "SET 4, B", 0 },
	{ "SET 4, C", 0 },
	{ "SET 4, D", 0 },
	{ "SET 4, E", 0 },
	{ "SET 4, H", 0 },
	{ "SET 4, L", 0 },
	{ "SET 4, (HL)", 0 },
	{ "SET 4, A", 0 },
	{ "SET 5, B", 0 },
	{ "SET 5, C", 0 },
	{ "SET 5, D", 0 },
	{ "SET 5, E", 0 },
	{ "SET 5, H", 0 },
	{ "SET 5, L", 0 },
	{ "SET 5, (HL)", 0 },
	{ "SET 5, A", 0 },
	{ "SET 6, B", 0 },
	{ "SET 6, C", 0 },
	{ "SET 6, D", 0 },
	{ "SET 6, E", 0 },
	{ "SET 6, H", 0 },
	{ "SET 6, L", 0 },
	{ "SET 6, (HL)", 0 },
	{ "SET 6, A", 0 },
	{ "SET 7, B", 0 },
	{ "SET 7, C", 0 },
	{ "SET 7, D", 0 },
	{ "SET 7, E", 0 },
	{ "SET 7, H", 0 },
	{ "SET 7, L", 0 },
	{ "SET 7, (HL)", 0 },
	{ "SET 7, A", 0 }
};

bool bitIsSet(uint8_t byte, int bit)
{
	return (byte & (1 << bit)) != 0;
}

uint8_t setBit(uint8_t byte, int bit)
{
	return byte | (1 << bit);
}

uint8_t clearBit(uint8_t byte, int bit)
{
	return byte & ~(1 << bit);
}

uint8_t getBit(uint8_t byte, int bit)
{
	return (byte >> bit) & 1;
}