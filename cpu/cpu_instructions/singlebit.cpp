#include "../CPU.h"

////////////////////////////////////////// BIT

/*!
 Method that checks a specific bit from a register.
 If the bit checked is set, then the zero flag is raised and cleared otherwise.
 The half carry flag is raised and the add sub flag cleared.
*/
void CPU::bit(REGISTER *reg, uint8_t position)
{
    if (bitIsSet(*reg, position))
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
}

NUM_CYCLES CPU::extendedOpcode0x40()
{
    bit(&registers.b, 0);
    return 8;
} // bit 0, B

NUM_CYCLES CPU::extendedOpcode0x41()
{
    bit(&registers.c, 0);
    return 8;
} // bit 0, C

NUM_CYCLES CPU::extendedOpcode0x42()
{
    bit(&registers.d, 0);
    return 8;
} // bit 0, D

NUM_CYCLES CPU::extendedOpcode0x43()
{
    bit(&registers.e, 0);
    return 8;
} // bit 0, E

NUM_CYCLES CPU::extendedOpcode0x44()
{
    bit(&registers.h, 0);
    return 8;
} // bit 0, H

NUM_CYCLES CPU::extendedOpcode0x45()
{
    bit(&registers.l, 0);
    return 8;
} // bit 0, L

NUM_CYCLES CPU::extendedOpcode0x46()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 0);
    return 12;
} // bit 0, (HL)

NUM_CYCLES CPU::extendedOpcode0x47()
{
    bit(&registers.a, 0);
    return 8;
} // bit 0, A

NUM_CYCLES CPU::extendedOpcode0x48()
{
    bit(&registers.b, 1);
    return 8;
} // bit 1, B

NUM_CYCLES CPU::extendedOpcode0x49()
{
    bit(&registers.c, 1);
    return 8;
} // bit 1, C

NUM_CYCLES CPU::extendedOpcode0x4A()
{
    bit(&registers.d, 1);
    return 8;
} // bit 1, D

NUM_CYCLES CPU::extendedOpcode0x4B()
{
    bit(&registers.e, 1);
    return 8;
} // bit 1, E

NUM_CYCLES CPU::extendedOpcode0x4C()
{
    bit(&registers.h, 1);
    return 8;
} // bit 1, H

NUM_CYCLES CPU::extendedOpcode0x4D()
{
    bit(&registers.l, 1);
    return 8;
} // bit 1, L

NUM_CYCLES CPU::extendedOpcode0x4E()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 1);
    return 12;
} // bit 1, (HL)

NUM_CYCLES CPU::extendedOpcode0x4F()
{
    bit(&registers.a, 1);
    return 8;
} // bit 1, A

NUM_CYCLES CPU::extendedOpcode0x50()
{
    bit(&registers.b, 2);
    return 8;
} // bit 2, B

NUM_CYCLES CPU::extendedOpcode0x51()
{
    bit(&registers.c, 2);
    return 8;
} // bit 2, C

NUM_CYCLES CPU::extendedOpcode0x52()
{
    bit(&registers.d, 2);
    return 8;
} // bit 2, D

NUM_CYCLES CPU::extendedOpcode0x53()
{
    bit(&registers.e, 2);
    return 8;
} // bit 2, E

NUM_CYCLES CPU::extendedOpcode0x54()
{
    bit(&registers.h, 2);
    return 8;
} // bit 2, H

NUM_CYCLES CPU::extendedOpcode0x55()
{
    bit(&registers.l, 2);
    return 8;
} // bit 2, L

NUM_CYCLES CPU::extendedOpcode0x56()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 2);
    return 12;
} // bit 2, (HL)

NUM_CYCLES CPU::extendedOpcode0x57()
{
    bit(&registers.a, 2);
    return 8;
} // bit 2, A

NUM_CYCLES CPU::extendedOpcode0x58()
{
    bit(&registers.b, 3);
    return 8;
} // bit 3, B

NUM_CYCLES CPU::extendedOpcode0x59()
{
    bit(&registers.c, 3);
    return 8;
} // bit 3, C

NUM_CYCLES CPU::extendedOpcode0x5A()
{
    bit(&registers.d, 3);
    return 8;
} // bit 3, D

NUM_CYCLES CPU::extendedOpcode0x5B()
{
    bit(&registers.e, 3);
    return 8;
} // bit 3, E

NUM_CYCLES CPU::extendedOpcode0x5C()
{
    bit(&registers.h, 3);
    return 8;
} // bit 3, H

NUM_CYCLES CPU::extendedOpcode0x5D()
{
    bit(&registers.l, 3);
    return 8;
} // bit 3, L

NUM_CYCLES CPU::extendedOpcode0x5E()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 3);
    return 12;
} // bit 3, (HL)

NUM_CYCLES CPU::extendedOpcode0x5F()
{
    bit(&registers.a, 3);
    return 8;
} // bit 3, A

NUM_CYCLES CPU::extendedOpcode0x60()
{
    bit(&registers.b, 4);
    return 8;
} // bit 4, B

NUM_CYCLES CPU::extendedOpcode0x61()
{
    bit(&registers.c, 4);
    return 8;
} // bit 4, C

NUM_CYCLES CPU::extendedOpcode0x62()
{
    bit(&registers.d, 4);
    return 8;
} // bit 4, D

NUM_CYCLES CPU::extendedOpcode0x63()
{
    bit(&registers.e, 4);
    return 8;
} // bit 4, E

NUM_CYCLES CPU::extendedOpcode0x64()
{
    bit(&registers.h, 4);
    return 8;
} // bit 4, H

NUM_CYCLES CPU::extendedOpcode0x65()
{
    bit(&registers.l, 4);
    return 8;
} // bit 4, L

NUM_CYCLES CPU::extendedOpcode0x66()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 4);
    return 12;
} // bit 4, (HL)

NUM_CYCLES CPU::extendedOpcode0x67()
{
    bit(&registers.a, 4);
    return 8;
} // bit 4, A

NUM_CYCLES CPU::extendedOpcode0x68()
{
    bit(&registers.b, 5);
    return 8;
} // bit 5, B

NUM_CYCLES CPU::extendedOpcode0x69()
{
    bit(&registers.c, 5);
    return 8;
} // bit 5, C

NUM_CYCLES CPU::extendedOpcode0x6A()
{
    bit(&registers.d, 5);
    return 8;
} // bit 5, D

NUM_CYCLES CPU::extendedOpcode0x6B()
{
    bit(&registers.e, 5);
    return 8;
} // bit 5, E

NUM_CYCLES CPU::extendedOpcode0x6C()
{
    bit(&registers.h, 5);
    return 8;
} // bit 5, H

NUM_CYCLES CPU::extendedOpcode0x6D()
{
    bit(&registers.l, 5);
    return 8;
} // bit 5, L

NUM_CYCLES CPU::extendedOpcode0x6E()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 5);
    return 12;
} // bit 5, (HL)

NUM_CYCLES CPU::extendedOpcode0x6F()
{
    bit(&registers.a, 5);
    return 8;
} // bit 5, A

NUM_CYCLES CPU::extendedOpcode0x70()
{
    bit(&registers.b, 6);
    return 8;
} // bit 6, B

NUM_CYCLES CPU::extendedOpcode0x71()
{
    bit(&registers.c, 6);
    return 8;
} // bit 6, C

NUM_CYCLES CPU::extendedOpcode0x72()
{
    bit(&registers.d, 6);
    return 8;
} // bit 6, D

NUM_CYCLES CPU::extendedOpcode0x73()
{
    bit(&registers.e, 6);
    return 8;
} // bit 6, E

NUM_CYCLES CPU::extendedOpcode0x74()
{
    bit(&registers.h, 6);
    return 8;
} // bit 6, H

NUM_CYCLES CPU::extendedOpcode0x75()
{
    bit(&registers.l, 6);
    return 8;
} // bit 6, L

NUM_CYCLES CPU::extendedOpcode0x76()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 6);
    return 12;
} // bit 6, (HL)

NUM_CYCLES CPU::extendedOpcode0x77()
{
    bit(&registers.a, 6);
    return 8;
} // bit 6, A

NUM_CYCLES CPU::extendedOpcode0x78()
{
    bit(&registers.b, 7);
    return 8;
} // bit 7, B

NUM_CYCLES CPU::extendedOpcode0x79()
{
    bit(&registers.c, 7);
    return 8;
} // bit 7, C

NUM_CYCLES CPU::extendedOpcode0x7A()
{
    bit(&registers.d, 7);
    return 8;
} // bit 7, D

NUM_CYCLES CPU::extendedOpcode0x7B()
{
    bit(&registers.e, 7);
    return 8;
} // bit 7, E

NUM_CYCLES CPU::extendedOpcode0x7C()
{
    bit(&registers.h, 7);
    return 8;
} // bit 7, H

NUM_CYCLES CPU::extendedOpcode0x7D()
{
    bit(&registers.l, 7);
    return 8;
} // bit 7, L

NUM_CYCLES CPU::extendedOpcode0x7E()
{
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 7);
    return 12;
} // bit 7, (HL)

NUM_CYCLES CPU::extendedOpcode0x7F()
{
    bit(&registers.a, 7);
    return 8;
} // bit 7, A

//////////////////////////////////////// RES

/*!
 Method that reset a specific bit from a register.
 */
void CPU::res(REGISTER *reg, uint8_t position)
{
    *reg &= ~(1 << position);
}

NUM_CYCLES CPU::extendedOpcode0x80()
{
    res(&registers.b, 0);
    return 8;
} // res 0, B

NUM_CYCLES CPU::extendedOpcode0x81()
{
    res(&registers.c, 0);
    return 8;
} // res 0, C

NUM_CYCLES CPU::extendedOpcode0x82()
{
    res(&registers.d, 0);
    return 8;
} // res 0, D

NUM_CYCLES CPU::extendedOpcode0x83()
{
    res(&registers.e, 0);
    return 8;
} // res 0, E

NUM_CYCLES CPU::extendedOpcode0x84()
{
    res(&registers.h, 0);
    return 8;
} // res 0, H

NUM_CYCLES CPU::extendedOpcode0x85()
{
    res(&registers.l, 0);
    return 8;
} // res 0, L

NUM_CYCLES CPU::extendedOpcode0x86()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 0);
    return 16;
} // res 0, (HL)

NUM_CYCLES CPU::extendedOpcode0x87()
{
    res(&registers.a, 0);
    return 8;
} // res 0, A

NUM_CYCLES CPU::extendedOpcode0x88()
{
    res(&registers.b, 1);
    return 8;
} // res 1, B

NUM_CYCLES CPU::extendedOpcode0x89()
{
    res(&registers.c, 1);
    return 8;
} // res 1, C

NUM_CYCLES CPU::extendedOpcode0x8A()
{
    res(&registers.d, 1);
    return 8;
} // res 1, D

NUM_CYCLES CPU::extendedOpcode0x8B()
{
    res(&registers.e, 1);
    return 8;
} // res 1, E

NUM_CYCLES CPU::extendedOpcode0x8C()
{
    res(&registers.h, 1);
    return 8;
} // res 1, H

NUM_CYCLES CPU::extendedOpcode0x8D()
{
    res(&registers.l, 1);
    return 8;
} // res 1, L

NUM_CYCLES CPU::extendedOpcode0x8E()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 1);
    return 16;
} // res 1, (HL)

NUM_CYCLES CPU::extendedOpcode0x8F()
{
    res(&registers.a, 1);
    return 8;
} // res 1, A

NUM_CYCLES CPU::extendedOpcode0x90()
{
    res(&registers.b, 2);
    return 8;
} // res 2, B

NUM_CYCLES CPU::extendedOpcode0x91()
{
    res(&registers.c, 2);
    return 8;
} // res 2, C

NUM_CYCLES CPU::extendedOpcode0x92()
{
    res(&registers.d, 2);
    return 8;
} // res 2, D

NUM_CYCLES CPU::extendedOpcode0x93()
{
    res(&registers.e, 2);
    return 8;
} // res 2, E

NUM_CYCLES CPU::extendedOpcode0x94()
{
    res(&registers.h, 2);
    return 8; // res 2, H
}

NUM_CYCLES CPU::extendedOpcode0x95()
{
    res(&registers.l, 2);
    return 8;
} // res 2, L

NUM_CYCLES CPU::extendedOpcode0x96()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 2);
    return 16;
} // res 2, (HL)

NUM_CYCLES CPU::extendedOpcode0x97()
{
    res(&registers.a, 2);
    return 8;
} // res 2, A

NUM_CYCLES CPU::extendedOpcode0x98()
{
    res(&registers.b, 3);
    return 8;
} // res 3, B

NUM_CYCLES CPU::extendedOpcode0x99()
{
    res(&registers.c, 3);
    return 8;
} // res 3, C

NUM_CYCLES CPU::extendedOpcode0x9A()
{
    res(&registers.d, 3);
    return 8;
} // res 3, D

NUM_CYCLES CPU::extendedOpcode0x9B()
{
    res(&registers.e, 3);
    return 8;
} // res 3, E

NUM_CYCLES CPU::extendedOpcode0x9C()
{
    res(&registers.h, 3);
    return 8;
} // res 3, H

NUM_CYCLES CPU::extendedOpcode0x9D()
{
    res(&registers.l, 3);
    return 8;
} // res 3, L

NUM_CYCLES CPU::extendedOpcode0x9E()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 3);
    return 16;
} // res 3, (HL)

NUM_CYCLES CPU::extendedOpcode0x9F()
{
    res(&registers.a, 3);
    return 8;
} // res 3, A

NUM_CYCLES CPU::extendedOpcode0xA0()
{
    res(&registers.b, 4);
    return 8;
} // res 4, B

NUM_CYCLES CPU::extendedOpcode0xA1()
{
    res(&registers.c, 4);
    return 8;
} // res 4, C

NUM_CYCLES CPU::extendedOpcode0xA2()
{
    res(&registers.d, 4);
    return 8;
} // res 4, D

NUM_CYCLES CPU::extendedOpcode0xA3()
{
    res(&registers.e, 4);
    return 8;
} // res 4, E

NUM_CYCLES CPU::extendedOpcode0xA4()
{
    res(&registers.h, 4);
    return 8;
} // res 4, H

NUM_CYCLES CPU::extendedOpcode0xA5()
{
    res(&registers.l, 4);
    return 8;
} // res 4, L

NUM_CYCLES CPU::extendedOpcode0xA6()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 4);
    return 16;
} // res 4, (HL)

NUM_CYCLES CPU::extendedOpcode0xA7()
{

    res(&registers.a, 4);
    return 8;
} // res 4, A

NUM_CYCLES CPU::extendedOpcode0xA8()
{
    res(&registers.b, 5);
    return 8;
} // res 5, B

NUM_CYCLES CPU::extendedOpcode0xA9()
{
    res(&registers.c, 5);

    return 8;
} // res 5, C

NUM_CYCLES CPU::extendedOpcode0xAA()
{
    res(&registers.d, 5);
    return 8;
} // res 5, D

NUM_CYCLES CPU::extendedOpcode0xAB()
{
    res(&registers.e, 5);
    return 8;
} // res 5, E

NUM_CYCLES CPU::extendedOpcode0xAC()
{
    res(&registers.h, 5);
    return 8;
} // res 5, H

NUM_CYCLES CPU::extendedOpcode0xAD()
{
    res(&registers.l, 5);
    return 8;
} // res 5, L

NUM_CYCLES CPU::extendedOpcode0xAE()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 5);
    return 16;
} // res 5, (HL)

NUM_CYCLES CPU::extendedOpcode0xAF()
{
    res(&registers.a, 5);
    return 8;
} // res 5, A

NUM_CYCLES CPU::extendedOpcode0xB0()
{
    res(&registers.b, 6);
    return 8;
} // res 6, B

NUM_CYCLES CPU::extendedOpcode0xB1()
{
    res(&registers.c, 6);
    return 8;
} // res 6, C

NUM_CYCLES CPU::extendedOpcode0xB2()
{
    res(&registers.d, 6);
    return 8;
} // res 6, D

NUM_CYCLES CPU::extendedOpcode0xB3()
{
    res(&registers.e, 6);
    return 8;
} // res 6, E

NUM_CYCLES CPU::extendedOpcode0xB4()
{
    res(&registers.h, 6);
    return 8;
} // res 6, H

NUM_CYCLES CPU::extendedOpcode0xB5()
{
    res(&registers.l, 6);
    return 8;
} // res 6, L

NUM_CYCLES CPU::extendedOpcode0xB6()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 6);
    return 16;
} // res 6, (HL)

NUM_CYCLES CPU::extendedOpcode0xB7()
{
    res(&registers.a, 6);
    return 8;
} // res 6, A

NUM_CYCLES CPU::extendedOpcode0xB8()
{
    res(&registers.b, 7);
    return 8;
} // res 7, B

NUM_CYCLES CPU::extendedOpcode0xB9()
{
    res(&registers.c, 7);
    return 8;
} // res 7, C

NUM_CYCLES CPU::extendedOpcode0xBA()
{
    res(&registers.d, 7);
    return 8;
} // res 7, D

NUM_CYCLES CPU::extendedOpcode0xBB()
{
    res(&registers.e, 7);
    return 8;
} // res 7, E

NUM_CYCLES CPU::extendedOpcode0xBC()
{
    res(&registers.h, 7);
    return 8;
} // res 7, H

NUM_CYCLES CPU::extendedOpcode0xBD()
{
    res(&registers.l, 7);
    return 8;
} // res 7, L

NUM_CYCLES CPU::extendedOpcode0xBE()
{
    uint8_t data = memory->readByte(registers.hl);
    res(&data, 7);
    return 16;
} // res 7, (HL)

NUM_CYCLES CPU::extendedOpcode0xBF()
{
    res(&registers.a, 7);
    return 8;
} // res 7, A

//////////////////////////////////////// SET

/*!
 Method that sets a specific bit from a register.
 */
void CPU::set(REGISTER *reg, uint8_t position)
{
    *reg |= (1 << position);
}

NUM_CYCLES CPU::extendedOpcode0xC0()
{
    set(&registers.b, 0);
    return 8;
} // set 0, B

NUM_CYCLES CPU::extendedOpcode0xC1()
{
    set(&registers.c, 0);
    return 8;
} // set 0, C

NUM_CYCLES CPU::extendedOpcode0xC2()
{
    set(&registers.d, 0);
    return 8;
} // set 0, D

NUM_CYCLES CPU::extendedOpcode0xC3()
{
    set(&registers.e, 0);
    return 8;
} // set 0, E

NUM_CYCLES CPU::extendedOpcode0xC4()
{
    set(&registers.h, 0);
    return 8;
} // set 0, H

NUM_CYCLES CPU::extendedOpcode0xC5()
{
    set(&registers.l, 0);
    return 8;
} // set 0, L

NUM_CYCLES CPU::extendedOpcode0xC6()
{
    uint8_t data = memory->readByte(registers.hl);
    return 16;
} // set 0, (HL)

NUM_CYCLES CPU::extendedOpcode0xC7()
{
    set(&registers.a, 0);
    return 8;
} // set 0, A

NUM_CYCLES CPU::extendedOpcode0xC8()
{
    set(&registers.b, 1);
    return 8;
} // set 1, B

NUM_CYCLES CPU::extendedOpcode0xC9()
{
    set(&registers.c, 1);
    return 8;
} // set 1, C

NUM_CYCLES CPU::extendedOpcode0xCA()
{
    set(&registers.d, 1);
    return 8;
} // set 1, D

NUM_CYCLES CPU::extendedOpcode0xCB()
{
    set(&registers.e, 1);
    return 8;
} // set 1, E

NUM_CYCLES CPU::extendedOpcode0xCC()
{
    set(&registers.h, 1);
    return 8;
} // set 1, H

NUM_CYCLES CPU::extendedOpcode0xCD()
{
    set(&registers.l, 1);
    return 8;
} // set 1, L

NUM_CYCLES CPU::extendedOpcode0xCE()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 1);
    return 16;
} // set 1, (HL)

NUM_CYCLES CPU::extendedOpcode0xCF()
{
    set(&registers.a, 1);
    return 8;
} // set 1, A

NUM_CYCLES CPU::extendedOpcode0xD0()
{
    set(&registers.b, 2);
    return 8;
} // set 2, B

NUM_CYCLES CPU::extendedOpcode0xD1()
{
    set(&registers.c, 2);
    return 8;
} // set 2, C

NUM_CYCLES CPU::extendedOpcode0xD2()
{
    set(&registers.d, 2);
    return 8;
} // set 2, D

NUM_CYCLES CPU::extendedOpcode0xD3()
{
    set(&registers.e, 2);
    return 8;
} // set 2, E

NUM_CYCLES CPU::extendedOpcode0xD4()
{
    set(&registers.h, 2);
    return 8;
} // set 2, H

NUM_CYCLES CPU::extendedOpcode0xD5()
{
    set(&registers.l, 2);
    return 8;
} // set 2, L

NUM_CYCLES CPU::extendedOpcode0xD6()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 2);
    return 16;
} // set 2, (HL)

NUM_CYCLES CPU::extendedOpcode0xD7()
{
    set(&registers.a, 2);
    return 8;
} // set 2, A

NUM_CYCLES CPU::extendedOpcode0xD8()
{
    set(&registers.b, 3);
    return 8;
} // set 3, B

NUM_CYCLES CPU::extendedOpcode0xD9()
{
    set(&registers.c, 3);
    return 8;
} // set 3, C

NUM_CYCLES CPU::extendedOpcode0xDA()
{
    set(&registers.d, 3);
    return 8;
} // set 3, D

NUM_CYCLES CPU::extendedOpcode0xDB()
{
    set(&registers.e, 3);
    return 8;
} // set 3, E

NUM_CYCLES CPU::extendedOpcode0xDC()
{
    set(&registers.h, 3);
    return 8;
} // set 3, H

NUM_CYCLES CPU::extendedOpcode0xDD()
{
    set(&registers.l, 3);
    return 8;
} // set 3, L

NUM_CYCLES CPU::extendedOpcode0xDE()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 3);
    return 16;
} // set 3, (HL)

NUM_CYCLES CPU::extendedOpcode0xDF()
{
    set(&registers.a, 3);
    return 8;
} // set 3, A

NUM_CYCLES CPU::extendedOpcode0xE0()
{
    set(&registers.b, 4);
    return 8;
} // set 4, B

NUM_CYCLES CPU::extendedOpcode0xE1()
{
    set(&registers.c, 4);
    return 8;
} // set 4, C

NUM_CYCLES CPU::extendedOpcode0xE2()
{
    set(&registers.d, 4);
    return 8;
} // set 4, D

NUM_CYCLES CPU::extendedOpcode0xE3()
{
    set(&registers.e, 4);
    return 8;
} // set 4, E

NUM_CYCLES CPU::extendedOpcode0xE4()
{
    set(&registers.h, 4);
    return 8;
} // set 4, H

NUM_CYCLES CPU::extendedOpcode0xE5()
{
    set(&registers.l, 4);
    return 8;
} // set 4, L

NUM_CYCLES CPU::extendedOpcode0xE6()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 4);
    return 16;
} // set 4, (HL)

NUM_CYCLES CPU::extendedOpcode0xE7()
{
    set(&registers.a, 4);
    return 8;
} // set 4, A

NUM_CYCLES CPU::extendedOpcode0xE8()
{
    set(&registers.b, 5);
    return 8;
} // set 5, B

NUM_CYCLES CPU::extendedOpcode0xE9()
{
    set(&registers.c, 5);
    return 8;
} // set 5, C

NUM_CYCLES CPU::extendedOpcode0xEA()
{
    set(&registers.d, 5);
    return 8;
} // set 5, D

NUM_CYCLES CPU::extendedOpcode0xEB()
{
    set(&registers.e, 5);
    return 8;
} // set 5, E

NUM_CYCLES CPU::extendedOpcode0xEC()
{
    set(&registers.h, 5);
    return 8;
} // set 5, H

NUM_CYCLES CPU::extendedOpcode0xED()
{
    set(&registers.l, 5);
    return 8;
} // set 5, L

NUM_CYCLES CPU::extendedOpcode0xEE()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 5);
    return 16;
} // set 5, (HL)

NUM_CYCLES CPU::extendedOpcode0xEF()
{
    set(&registers.a, 5);
    return 8;
} // set 5, A

NUM_CYCLES CPU::extendedOpcode0xF0()
{
    set(&registers.b, 6);
    return 8;
} // set 6, B

NUM_CYCLES CPU::extendedOpcode0xF1()
{
    set(&registers.c, 6);
    return 8;
} // set 6, C

NUM_CYCLES CPU::extendedOpcode0xF2()
{
    set(&registers.d, 6);
    return 8;
} // set 6, D

NUM_CYCLES CPU::extendedOpcode0xF3()
{
    set(&registers.e, 6);
    return 8;
} // set 6, E

NUM_CYCLES CPU::extendedOpcode0xF4()
{
    set(&registers.h, 6);
    return 8;
} // set 6, H

NUM_CYCLES CPU::extendedOpcode0xF5()
{
    set(&registers.l, 6);
    return 8;
} // set 6, L

NUM_CYCLES CPU::extendedOpcode0xF6()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 6);
    return 16;
} // set 6, (HL)

NUM_CYCLES CPU::extendedOpcode0xF7()
{
    set(&registers.a, 6);
    return 8;
} // set 6, A

NUM_CYCLES CPU::extendedOpcode0xF8()
{
    set(&registers.b, 7);
    return 8;
} // set 7, B

NUM_CYCLES CPU::extendedOpcode0xF9()
{
    set(&registers.c, 7);
    return 8;
} // set 7, C

NUM_CYCLES CPU::extendedOpcode0xFA()
{
    set(&registers.d, 7);
    return 8;
} // set 7, D

NUM_CYCLES CPU::extendedOpcode0xFB()
{
    set(&registers.e, 7);
    return 8;
} // set 7, E

NUM_CYCLES CPU::extendedOpcode0xFC()
{
    set(&registers.h, 7);
    return 8;
} // set 7, H

NUM_CYCLES CPU::extendedOpcode0xFD()
{
    set(&registers.l, 7);
    return 8;
} // set 7, L

NUM_CYCLES CPU::extendedOpcode0xFE()
{
    uint8_t data = memory->readByte(registers.hl);
    set(&data, 7);
    return 16;
} // set 7, (HL)

NUM_CYCLES CPU::extendedOpcode0xFF()
{
    set(&registers.a, 7);
    return 8;
} // set 7, A