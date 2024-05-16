#include "registers.h"
#include <stdexcept>

Registers::Registers()
{
    reset();
}

void Registers::reset()
{
    af = 0x01B0;
    bc = 0x0013;
    de = 0x00D8;
    hl = 0x014D;
    sp = 0xFFFE;
    pc = 0x0100;

    flags.zero = false;
    flags.addSubtract = false;
    flags.half_carry = false;
    flags.carry = false;
}

void Registers::setFirstByte(uint8_t byte, enum RegisterTypes reg)
{
    switch (reg)
    {
        case RegisterTypes::A:
            a = byte;
            break;
        case RegisterTypes::C:
            c = byte;
            break;
        case RegisterTypes::E:
            e = byte;
            break;
        case RegisterTypes::L:
            l = byte;
            break;
        default:
            std::invalid_argument("Invalid register type");
            break;
    }
}

void Registers::setSecondByte(uint8_t byte, enum RegisterTypes reg)
{
    switch (reg)
    {
        case RegisterTypes::F:
            f = byte;
            break;
        case RegisterTypes::B:
            b = byte;
            break;
        case RegisterTypes::D:
            d = byte;
            break;
        case RegisterTypes::H:
            h = byte;
            break;
        default:
            std::invalid_argument("Invalid register type");
            break;
    
    }
}

void Registers::setTwoBytes(uint16_t word, enum RegisterTypes reg)
{
    switch (reg)
    {
        case RegisterTypes::AF:
            af = word;
            break;
        case RegisterTypes::BC:
            bc = word;
            break;
        case RegisterTypes::DE:
            de = word;
            break;
        case RegisterTypes::HL:
            hl = word;
            break;
        case RegisterTypes::SP:
            sp = word;
            break;
        case RegisterTypes::PC:
            pc = word;
            break;
        default:
            std::invalid_argument("Invalid register type");
            break;
    }
}


void Registers::numToFlags(uint8_t byte)
{
    uint8_t zero = (( byte >> 7 ) & 0b1) == 1;
    uint8_t subtract = (( byte >> 6 ) & 0b1) == 1;
    uint8_t half_carry = (( byte >> 5 ) & 0b1) == 1;
    uint8_t carry = (( byte >> 4 ) & 0b1) == 1;

    flags.zero = zero;
    flags.addSubtract = subtract;
    flags.half_carry = half_carry;
    flags.carry = carry;

}

uint8_t Registers::flagsToNum() {
    uint8_t zero = flags.zero;
    uint8_t subtract = flags.addSubtract;
    uint8_t half_carry = flags.half_carry;
    uint8_t carry = flags.carry;

    return (zero << 7) | (subtract << 6) | (half_carry << 5) | (carry << 4);
}


void Registers::flags::raiseFlag(enum FlagTypes flag)
{
    switch (flag)
    {
        case FlagTypes::ZERO:
            zero = true;
            *f = *f | 0b10000000;
            break;
        case FlagTypes::CARRY:
            carry = true;
            *f = *f | 0b00010000;
            break;
        case FlagTypes::HALF_CARRY:
            half_carry = true;
            *f = *f | 0b00100000;
            break;
        case FlagTypes::ADDSUB:
            addSubtract = true;
            *f = *f | 0b01000000;
            break;
        default:
            std::invalid_argument("Invalid flag type");
            break;
    }
    // lower the lower 4 bits of the flag register
    *f = *f & 0b11110000;
}

void Registers::flags::lowerFlag(enum FlagTypes flag)
{
    switch (flag)
    {
        case FlagTypes::ZERO:
            zero = false;
            *f = *f & 0b01111111;
            break;
        case FlagTypes::CARRY:
            carry = false;
            *f = *f & 0b11101111;
            break;
        case FlagTypes::HALF_CARRY:
            half_carry = false;
            *f = *f & 0b11011111;
            break;
        case FlagTypes::ADDSUB:
            addSubtract = false;
            *f = *f & 0b10111111;
            break;
        default:
            std::invalid_argument("Invalid flag type");
            break;
    }
    // lower the lower 4 bits of the flag register
    *f = *f & 0b11110000;
}

bool Registers::flags::getFlag(enum FlagTypes flag)
{
   // checks f bitwise
    switch (flag)
    {
        case FlagTypes::ZERO:
            return *f & 0b10000000;
        case FlagTypes::CARRY:
            return *f & 0b00010000;
        case FlagTypes::HALF_CARRY:
            return *f & 0b00100000;
        case FlagTypes::ADDSUB:
            return *f & 0b01000000;
        default:
            std::invalid_argument("Invalid flag type");
            return false;
    }
}

void Registers::flags::reset()
{
    *f = 0x00;
    zero = false;
    carry = false;
    half_carry = false;
    addSubtract = false;
}