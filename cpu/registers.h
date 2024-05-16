#pragma once

#include <cstdint>
#include <string>

#include "../common/defs.h"

struct Registers
{
    union
    {
        struct
        {
            uint8_t f; 
            uint8_t a; // high byte
        };
        uint16_t af; // 16-bit register
    };

    union
    {
        struct
        {
            uint8_t c; // low byte
            uint8_t b; // high byte
        };
        uint16_t bc; // 16-bit register
    };

    union
    {
        struct
        {
            uint8_t e; // low byte
            uint8_t d; // high byte
        };
        uint16_t de; // 16-bit register
    }; 

    union
    {
        struct
        {
            uint8_t l; // low byte
            uint8_t h; // high byte
        };
        uint16_t hl; // 16-bit register
    };

    uint16_t sp; // stack pointer
    uint16_t pc; // program counter

    Registers();

    void reset();
    void setFirstByte(uint8_t byte, enum RegisterTypes reg);
    void setSecondByte(uint8_t byte, enum RegisterTypes reg);
    void setTwoBytes(uint16_t word, enum RegisterTypes reg);

    uint8_t flag;

    struct flags
    {
        uint8_t* f;
        // zf in documentation
        bool zero;
        // n in documentation
        bool addSubtract;
        // h in documentation
        bool half_carry;
        // cy in documentation
        bool carry;

        void raiseFlag(enum FlagTypes flag);
        void lowerFlag(enum FlagTypes flag);
        bool getFlag(enum FlagTypes flag);
        void reset();

    } flags;

    void numToFlags(uint8_t byte);
    uint8_t flagsToNum();

    bool ime; // interrupt master enable
};

