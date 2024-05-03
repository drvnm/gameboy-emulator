#include "../cpu.h"
#include "../../common/defs.h"

void CPU::add8bit(REGISTER *reg, uint8_t value)
{
    if (*reg + value > 0xFF)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }
    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if (*reg + value == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }

    if (((*reg & 0xF) + (value & 0xF)) > 0xF)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }

    *reg += value;
}

NUM_CYCLES CPU::opcode0x87()
{
    add8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0x80()
{
    add8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0x81()
{
    add8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0x82()
{
    add8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0x83()
{
    add8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0x84()
{
    add8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0x85()
{
    add8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0x86()
{
    add8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xC6()
{
    add8bit(&registers.a, rom[registers.pc + 1]);
    return 8;
}

// ADC INSTRUCTIONS
void CPU::adc8bit(REGISTER *reg, uint8_t value)
{
    uint8_t carry = registers.flags.carry ? 0b1 : 0b0;
    uint8_t result = *reg + value + carry;

    if (result > 0xFF)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }
    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if (result == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }

    if (((*reg & 0xF) + (value & 0xF) + carry) > 0xF)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }

    *reg += result;
}

NUM_CYCLES CPU::opcode0x8F()
{
    adc8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0x88()
{
    adc8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0x89()
{
    adc8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0x8A()
{
    adc8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0x8B()
{
    adc8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0x8C()
{
    adc8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0x8D()
{
    adc8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0x8E()
{
    adc8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xCE()
{
    adc8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}

// SUB INSTRUCTIONS
void CPU::sub8bit(REGISTER *reg, uint8_t value)
{
    if (*reg - value < 0)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }
    registers.flags.raiseFlag(FlagTypes::ADDSUB);

    if (*reg - value == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }

    if (((*reg & 0xF) - (value & 0xF)) < 0)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }

    *reg -= value;
}

NUM_CYCLES CPU::opcode0x97()
{
    sub8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0x90()
{
    sub8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0x91()
{
    sub8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0x92()
{
    sub8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0x93()
{
    sub8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0x94()
{
    sub8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0x95()
{
    sub8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0x96()
{
    sub8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xD6()
{
    sub8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}
// SBC INSTRUCTIONS
void CPU::sbc8bit(REGISTER *reg, uint8_t value)
{
    uint8_t carry = registers.flags.carry ? 0b1 : 0b0;
    uint8_t result = *reg - value - carry;

    if (result < 0)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }
    registers.flags.raiseFlag(FlagTypes::ADDSUB);

    if (result == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }

    if (((*reg & 0xF) - (value & 0xF) - carry) < 0)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }

    *reg -= result;
}

NUM_CYCLES CPU::opcode0x9F()
{
    sbc8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0x98()
{
    sbc8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0x99()
{
    sbc8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0x9A()
{
    sbc8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0x9B()
{
    sbc8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0x9C()
{
    sbc8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0x9D()
{
    sbc8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0x9E()
{
    sbc8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xDE()
{
    sbc8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}

// AND INSTRUCTIONS
void CPU::and8bit(REGISTER *reg, uint8_t value)
{
    *reg &= value;
    registers.flags.lowerFlag(FlagTypes::CARRY);
    registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::opcode0xA7()
{
    and8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0xA0()
{
    and8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0xA1()
{
    and8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0xA2()
{
    and8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0xA3()
{
    and8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0xA4()
{
    and8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0xA5()
{
    and8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0xA6()
{
    and8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xE6()
{
    and8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}

// OR INSTRUCTIONS
void CPU::or8bit(REGISTER *reg, uint8_t value)
{
    *reg |= value;
    registers.flags.lowerFlag(FlagTypes::CARRY);
    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::opcode0xB7()
{
    or8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0xB0()
{
    or8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0xB1()
{
    or8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0xB2()
{
    or8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0xB3()
{
    or8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0xB4()
{
    or8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0xB5()
{
    or8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0xB6()
{
    or8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xF6()
{
    or8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}

// XOR INSTRUCTIONS
void CPU::xor8bit(REGISTER *reg, uint8_t value)
{
    *reg ^= value;
    registers.flags.lowerFlag(FlagTypes::CARRY);
    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::opcode0xAF()
{
    xor8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0xA8()
{
    xor8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0xA9()
{
    xor8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0xAA()
{
    xor8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0xAB()
{
    xor8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0xAC()
{
    xor8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0xAD()
{
    xor8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0xAE()
{
    xor8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xEE()
{
    xor8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}

// CP INSTRUCTIONS
void CPU::cp8bit(REGISTER *reg, uint8_t value)
{
    registers.flags.reset();
    registers.flags.raiseFlag(FlagTypes::ADDSUB);
    if (*reg == value)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    if (*reg < value)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if (((*reg & 0x0F) < (value & 0x0F)))
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
}

NUM_CYCLES CPU::opcode0xBF()
{
    cp8bit(&registers.a, registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0xB8()
{
    cp8bit(&registers.a, registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0xB9()
{
    cp8bit(&registers.a, registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0xBA()
{
    cp8bit(&registers.a, registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0xBB()
{
    cp8bit(&registers.a, registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0xBC()
{
    cp8bit(&registers.a, registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0xBD()
{
    cp8bit(&registers.a, registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0xBE()
{
    cp8bit(&registers.a, rom[registers.hl]);
    return 8;
}

NUM_CYCLES CPU::opcode0xFE()
{
    cp8bit(&registers.a, rom[registers.pc]);
    registers.pc++;
    return 8;
}

// INC INSTRUCTIONS
void CPU::inc8bit(REGISTER *reg)
{
    *reg++;
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    if ((*reg & 0x0F) == 0)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }
}

NUM_CYCLES CPU::opcode0x3C()
{
    inc8bit(&registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0x04()
{
    inc8bit(&registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0x0C()
{
    inc8bit(&registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0x14()
{
    inc8bit(&registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0x1C()
{
    inc8bit(&registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0x24()
{
    inc8bit(&registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0x2C()
{
    inc8bit(&registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0x34()
{
    inc8bit(&rom[registers.hl]);
    return 12;
}

// DEC INSTRUCTIONS
void CPU::dec8bit(REGISTER *reg)
{
    *reg--;
    registers.flags.raiseFlag(FlagTypes::ADDSUB);
    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    if ((*reg & 0x0F) == 0)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }
}

NUM_CYCLES CPU::opcode0x3D()
{
    dec8bit(&registers.a);
    return 4;
}

NUM_CYCLES CPU::opcode0x05()
{
    dec8bit(&registers.b);
    return 4;
}

NUM_CYCLES CPU::opcode0x0D()
{
    dec8bit(&registers.c);
    return 4;
}

NUM_CYCLES CPU::opcode0x15()
{
    dec8bit(&registers.d);
    return 4;
}

NUM_CYCLES CPU::opcode0x1D()
{
    dec8bit(&registers.e);
    return 4;
}

NUM_CYCLES CPU::opcode0x25()
{
    dec8bit(&registers.h);
    return 4;
}

NUM_CYCLES CPU::opcode0x2D()
{
    dec8bit(&registers.l);
    return 4;
}

NUM_CYCLES CPU::opcode0x35()
{
    dec8bit(&rom[registers.hl]);
    return 12;
}

// DAA INSTRUCTIONS
NUM_CYCLES CPU::opcode0x27()
{
    if (registers.flags.addSubtract)
    {
        if (registers.flags.half_carry)
        {
            registers.a -= 0x06;
        }
        if (registers.flags.carry)
        {
            registers.a -= 0x60;
        }
    }
    else
    {
        if ((registers.a & 0x0F) > 0x09 || registers.flags.half_carry)
        {
            registers.a += 0x06;
        }
        if (registers.a > 0x9F || registers.flags.carry)
        {
            registers.a += 0x60;
        }
    }

    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    if (registers.a > 0xFF)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    registers.flags.lowerFlag(FlagTypes::ZERO);

    return 4;
}

// CPL INSTRUCTIONS
NUM_CYCLES CPU::opcode0x2F()
{
    registers.a = ~registers.a;
    registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    registers.flags.raiseFlag(FlagTypes::ADDSUB);
    return 4;
}