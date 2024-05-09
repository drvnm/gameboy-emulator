#pragma once

#include <cstdint>


enum RegisterTypes
{
    A,
    B,
    C,
    D,
    E,
    F,
    H,
    L,

    // others
    SP,
    PC,

    // dual registers
    AF,
    BC,
    DE,
    HL

};

enum FlagTypes
{
    ZERO,
    ADDSUB,
    CARRY,
    HALF_CARRY,
};

#define NUM_CYCLES short
#define REGISTER uint8_t
#define REGISTER16 uint16_t
#define OPCODE uint8_t

struct opcodeInfo
{
    const char *name;
    int size;
};

#define NUM_OPCODES 256
extern opcodeInfo opcodeDescriptionTable[NUM_OPCODES];
extern opcodeInfo extendedOpcodeDescriptionTable[NUM_OPCODES];
struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

	bool isEqual(RGB other) const {
		return red == other.red && green == other.green && blue == other.blue;
	}
};


// returns true if the bit at position is set
bool bitIsSet(uint8_t byte, int position);
uint8_t setBit(uint8_t byte, int position);
uint8_t clearBit(uint8_t byte, int position);
uint8_t getBit(uint8_t byte, int position);