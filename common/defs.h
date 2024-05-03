#pragma once

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

enum FlagTypes {
    ZERO,
    ADDSUB,
    CARRY,
    HALF_CARRY,
};

#define NUM_CYCLES short
#define REGISTER uint8_t
#define OPCODE uint8_t