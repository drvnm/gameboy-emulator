#include "../cpu.h"
#include "../../common/defs.h"
#include <iostream>

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

    if ((*reg + value) & 0xFF)
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }

    if (((*reg & 0x0F) + (value & 0x0F)) > 0x0F)
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
} // ADD A A

NUM_CYCLES CPU::opcode0x80()
{
    add8bit(&registers.a, registers.b);
    return 4;
} // ADD A B

void CPU::add16bit(REGISTER16 *reg, uint16_t value)
{
    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if (((*reg & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }

    if (*reg + value > 0xFFFF)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }

    *reg += value;
}

NUM_CYCLES CPU::opcode0x09()
{
    add16bit(&registers.hl, registers.bc);
    return 8;
} // ADD HL BC

NUM_CYCLES CPU::opcode0x19()
{
    add16bit(&registers.hl, registers.de);
    return 8;
} // ADD HL DE

NUM_CYCLES CPU::opcode0x29()
{
    add16bit(&registers.hl, registers.hl);
    return 8;
} // ADD HL HL

NUM_CYCLES CPU::opcode0x39()
{
    add16bit(&registers.hl, registers.sp);
    return 8;
} // ADD HL SP

NUM_CYCLES CPU::opcode0xE8()
{
    registers.pc += 1;
    char data = memory->readByte(registers.pc);
    registers.flags.reset();

    if ((registers.sp & 0x0F) + (data & 0x0F) > 0x0F)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }

    if ((registers.sp & 0xFF) + (data & 0xFF) > 0xFF)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    registers.sp += (uint16_t)data;
    return 16;

} // ADD SP n

NUM_CYCLES CPU::opcode0x81()
{
    add8bit(&registers.a, registers.c);
    return 4;
} // ADD A C

NUM_CYCLES CPU::opcode0x82()
{
    add8bit(&registers.a, registers.d);
    return 4;
} // ADD A D

NUM_CYCLES CPU::opcode0x83()
{
    add8bit(&registers.a, registers.e);
    return 4;
} // ADD A E

NUM_CYCLES CPU::opcode0x84()
{
    add8bit(&registers.a, registers.h);
    return 4;
} // ADD A H

NUM_CYCLES CPU::opcode0x85()
{
    add8bit(&registers.a, registers.l);
    return 4;
} // ADD A L

NUM_CYCLES CPU::opcode0x86()
{
    add8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // ADD A (HL)

NUM_CYCLES CPU::opcode0xC6()
{
    registers.pc += 1;
    add8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // ADD A n

// ADC INSTRUCTIONS
void CPU::adc8bit(REGISTER *reg, uint8_t value)
{
    uint8_t carry = registers.flags.getFlag(FlagTypes::CARRY) ? 0b1 : 0b0;
    uint16_t result = *reg + value + carry;

    registers.flags.lowerFlag(FlagTypes::ADDSUB);

    if ((result & 0xFF) == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }

    if (result > 0xFF)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }

    if (((*reg & 0x0F) + (value & 0x0F) + carry) > 0x0F)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }

    *reg = result & 0xFF;
}

NUM_CYCLES CPU::opcode0x8F()
{
    adc8bit(&registers.a, registers.a);
    return 4;
} // ADC A A

NUM_CYCLES CPU::opcode0x88()
{
    adc8bit(&registers.a, registers.b);
    return 4;
} // ADC A B

NUM_CYCLES CPU::opcode0x89()
{
    adc8bit(&registers.a, registers.c);
    return 4;
} // ADC A C

NUM_CYCLES CPU::opcode0x8A()
{
    adc8bit(&registers.a, registers.d);
    return 4;
} // ADC A D

NUM_CYCLES CPU::opcode0x8B()
{
    adc8bit(&registers.a, registers.e);
    return 4;
} // ADC A E

NUM_CYCLES CPU::opcode0x8C()
{
    adc8bit(&registers.a, registers.h);
    return 4;
} // ADC A H

NUM_CYCLES CPU::opcode0x8D()
{
    adc8bit(&registers.a, registers.l);
    return 4;
} // ADC A L

NUM_CYCLES CPU::opcode0x8E()
{
    adc8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // ADC A (HL)

NUM_CYCLES CPU::opcode0xCE()
{
    registers.pc += 1;
    adc8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // ADC A n

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
} // SUB A A

NUM_CYCLES CPU::opcode0x90()
{
    sub8bit(&registers.a, registers.b);
    return 4;
} // SUB A B

NUM_CYCLES CPU::opcode0x91()
{
    sub8bit(&registers.a, registers.c);
    return 4;
} // SUB A C

NUM_CYCLES CPU::opcode0x92()
{
    sub8bit(&registers.a, registers.d);
    return 4;
} // SUB A D

NUM_CYCLES CPU::opcode0x93()
{
    sub8bit(&registers.a, registers.e);
    return 4;
} // SUB A E

NUM_CYCLES CPU::opcode0x94()
{
    sub8bit(&registers.a, registers.h);
    return 4;
} // SUB A H

NUM_CYCLES CPU::opcode0x95()
{
    sub8bit(&registers.a, registers.l);
    return 4;
} // SUB A L

NUM_CYCLES CPU::opcode0x96()
{
    sub8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // SUB A (HL)

NUM_CYCLES CPU::opcode0xD6()
{
    registers.pc += 1;
    sub8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // SUB A n
// SBC INSTRUCTIONS
void CPU::sbc8bit(REGISTER *reg, uint8_t value)
{
    int carry = registers.flags.getFlag(FlagTypes::CARRY) ? 1 : 0;
    int result = *reg - value - carry;

    registers.flags.reset();
    registers.flags.raiseFlag(FlagTypes::ADDSUB);

    if ((result & 0xFF) == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }

    if (result < 0)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if (((*reg & 0x0F) - (value & 0x0F) - carry) < 0)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }

    *reg = result & 0xFF;
}

NUM_CYCLES CPU::opcode0x9F()
{
    sbc8bit(&registers.a, registers.a);
    return 4;
} // SBC A A

NUM_CYCLES CPU::opcode0x98()
{
    sbc8bit(&registers.a, registers.b);
    return 4;
} // SBC A B

NUM_CYCLES CPU::opcode0x99()
{
    sbc8bit(&registers.a, registers.c);
    return 4;
} // SBC A C

NUM_CYCLES CPU::opcode0x9A()
{
    sbc8bit(&registers.a, registers.d);
    return 4;
} // SBC A D

NUM_CYCLES CPU::opcode0x9B()
{
    sbc8bit(&registers.a, registers.e);
    return 4;
} // SBC A E

NUM_CYCLES CPU::opcode0x9C()
{
    sbc8bit(&registers.a, registers.h);
    return 4;
} // SBC A H

NUM_CYCLES CPU::opcode0x9D()
{
    sbc8bit(&registers.a, registers.l);
    return 4;
} // SBC A L

NUM_CYCLES CPU::opcode0x9E()
{
    sbc8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // SBC A (HL)

NUM_CYCLES CPU::opcode0xDE()
{
    registers.pc += 1;
    sbc8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // SBC A n

// AND INSTRUCTIONS
void CPU::and8bit(REGISTER *reg, uint8_t value)
{
    *reg &= value;
    registers.flags.reset();
    registers.flags.raiseFlag(FlagTypes::HALF_CARRY);

    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::opcode0xA7()
{
    and8bit(&registers.a, registers.a);
    return 4;
} // AND A A

NUM_CYCLES CPU::opcode0xA0()
{
    and8bit(&registers.a, registers.b);
    return 4;
} // AND A B

NUM_CYCLES CPU::opcode0xA1()
{
    and8bit(&registers.a, registers.c);
    return 4;
} // AND A C

NUM_CYCLES CPU::opcode0xA2()
{
    and8bit(&registers.a, registers.d);
    return 4;
} // AND A D

NUM_CYCLES CPU::opcode0xA3()
{
    and8bit(&registers.a, registers.e);
    return 4;
} // AND A E

NUM_CYCLES CPU::opcode0xA4()
{
    and8bit(&registers.a, registers.h);
    return 4;
} // AND A H

NUM_CYCLES CPU::opcode0xA5()
{
    and8bit(&registers.a, registers.l);
    return 4;
} // AND A L

NUM_CYCLES CPU::opcode0xA6()
{
    and8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // AND A (HL)

NUM_CYCLES CPU::opcode0xE6()
{
    registers.pc += 1;
    and8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // AND A n

// OR INSTRUCTIONS
void CPU::or8bit(REGISTER *reg, uint8_t value)
{
    *reg |= value;

    registers.flags.reset();

    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::opcode0xB7()
{
    or8bit(&registers.a, registers.a);
    return 4;
} // OR A A

NUM_CYCLES CPU::opcode0xB0()
{
    or8bit(&registers.a, registers.b);
    return 4;
} // OR A B

NUM_CYCLES CPU::opcode0xB1()
{
    or8bit(&registers.a, registers.c);
    return 4;
} // OR A C

NUM_CYCLES CPU::opcode0xB2()
{
    or8bit(&registers.a, registers.d);
    return 4;
} // OR A D

NUM_CYCLES CPU::opcode0xB3()
{
    or8bit(&registers.a, registers.e);
    return 4;
} // OR A E

NUM_CYCLES CPU::opcode0xB4()
{
    or8bit(&registers.a, registers.h);
    return 4;
} // OR A H

NUM_CYCLES CPU::opcode0xB5()
{
    or8bit(&registers.a, registers.l);
    return 4;
} // OR A L

NUM_CYCLES CPU::opcode0xB6()
{
    or8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // OR A (HL)

NUM_CYCLES CPU::opcode0xF6()
{
    registers.pc += 1;
    or8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // OR A n

// XOR INSTRUCTIONS
void CPU::xor8bit(REGISTER *reg, uint8_t value)
{
    *reg ^= value;

    registers.flags.reset();

    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::opcode0xAF()
{
    xor8bit(&registers.a, registers.a);
    return 4;
} // XOR A A
NUM_CYCLES CPU::opcode0xA8()
{
    xor8bit(&registers.a, registers.b);
    return 4;
} // XOR A B

NUM_CYCLES CPU::opcode0xA9()
{
    xor8bit(&registers.a, registers.c);
    return 4;
} // XOR A C

NUM_CYCLES CPU::opcode0xAA()
{
    xor8bit(&registers.a, registers.d);
    return 4;
} // XOR A D

NUM_CYCLES CPU::opcode0xAB()
{
    xor8bit(&registers.a, registers.e);
    return 4;
} // XOR A E

NUM_CYCLES CPU::opcode0xAC()
{
    xor8bit(&registers.a, registers.h);
    return 4;
} // XOR A H

NUM_CYCLES CPU::opcode0xAD()
{
    xor8bit(&registers.a, registers.l);
    return 4;
} // XOR A L

NUM_CYCLES CPU::opcode0xAE()
{
    xor8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // XOR A (HL)

NUM_CYCLES CPU::opcode0xEE()
{
    registers.pc += 1;
    xor8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // XOR A n

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
} // CP A A

NUM_CYCLES CPU::opcode0xB8()
{
    cp8bit(&registers.a, registers.b);
    return 4;
} // CP A B

NUM_CYCLES CPU::opcode0xB9()
{
    cp8bit(&registers.a, registers.c);
    return 4;
} // CP A C

NUM_CYCLES CPU::opcode0xBA()
{
    cp8bit(&registers.a, registers.d);
    return 4;
} // CP A D

NUM_CYCLES CPU::opcode0xBB()
{
    cp8bit(&registers.a, registers.e);
    return 4;
} // CP A E

NUM_CYCLES CPU::opcode0xBC()
{
    cp8bit(&registers.a, registers.h);
    return 4;
} // CP A H

NUM_CYCLES CPU::opcode0xBD()
{
    cp8bit(&registers.a, registers.l);
    return 4;
} // CP A L

NUM_CYCLES CPU::opcode0xBE()
{
    cp8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // CP A (HL)

NUM_CYCLES CPU::opcode0xFE()
{
    registers.pc += 1;
    cp8bit(&registers.a, memory->readByte(registers.pc));
    return 8;
} // CP A n

// INC INSTRUCTIONS
void CPU::inc8bit(REGISTER *reg)
{
    *reg = *reg + 1;
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }
    if (*reg & 0x0F)
    {
        registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    }
    else
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
}

NUM_CYCLES CPU::opcode0x3C()
{
    inc8bit(&registers.a);
    return 4;
} // INC A

NUM_CYCLES CPU::opcode0x04()
{
    inc8bit(&registers.b);
    return 4;
} // INC B

NUM_CYCLES CPU::opcode0x0C()
{
    inc8bit(&registers.c);
    return 4;
} // INC C

NUM_CYCLES CPU::opcode0x14()
{
    inc8bit(&registers.d);
    return 4;
} // INC D

NUM_CYCLES CPU::opcode0x1C()
{
    inc8bit(&registers.e);
    return 4;
} // INC E

NUM_CYCLES CPU::opcode0x24()
{
    inc8bit(&registers.h);
    return 4;
} // INC H

NUM_CYCLES CPU::opcode0x2C()
{
    inc8bit(&registers.l);
    return 4;
} // INC L

NUM_CYCLES CPU::opcode0x34()
{
    uint8_t value = memory->readByte(registers.hl);
    inc8bit(&value);
    memory->writeByte(registers.hl, value);
    return 12;
} // INC (HL)

void CPU::inc16bit(REGISTER16 *reg)
{
    *reg += 1;
}

NUM_CYCLES CPU::opcode0x03()
{
    inc16bit(&registers.bc);
    return 8;
} // INC BC

NUM_CYCLES CPU::opcode0x13()
{
    inc16bit(&registers.de);
    return 8;
} // INC DE

NUM_CYCLES CPU::opcode0x23()
{
    inc16bit(&registers.hl);
    return 8;
} // INC HL

NUM_CYCLES CPU::opcode0x33()
{
    inc16bit(&registers.sp);
    return 8;
} // INC SP

// DEC INSTRUCTIONS
void CPU::dec8bit(REGISTER *reg)
{
    *reg = *reg - 1;
    registers.flags.raiseFlag(FlagTypes::ADDSUB);
    if (*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
    else
    {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    }

    if ((*reg & 0x0F) == 0x0F)
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
} // DEC A

NUM_CYCLES CPU::opcode0x05()
{
    dec8bit(&registers.b);
    return 4;
} // DEC B

NUM_CYCLES CPU::opcode0x0D()
{
    dec8bit(&registers.c);
    return 4;
} // DEC C

NUM_CYCLES CPU::opcode0x15()
{
    dec8bit(&registers.d);
    return 4;
} // DEC D

NUM_CYCLES CPU::opcode0x1D()
{
    dec8bit(&registers.e);
    return 4;
} // DEC E

NUM_CYCLES CPU::opcode0x25()
{
    dec8bit(&registers.h);
    return 4;
} // DEC H

NUM_CYCLES CPU::opcode0x2D()
{
    dec8bit(&registers.l);
    return 4;
} // DEC L

NUM_CYCLES CPU::opcode0x35()
{
    uint8_t value = memory->readByte(registers.hl);
    dec8bit(&value);
    memory->writeByte(registers.hl, value);
    return 12;
} // DEC (HL)

void CPU::dec16bit(REGISTER16 *reg)
{
    *reg -= 1;
}

NUM_CYCLES CPU::opcode0x0B()
{
    dec16bit(&registers.bc);
    return 8;
} // DEC BC

NUM_CYCLES CPU::opcode0x1B()
{
    dec16bit(&registers.de);
    return 8;
} // DEC DE

NUM_CYCLES CPU::opcode0x2B()
{
    dec16bit(&registers.hl);
    return 8;
} // DEC HL

NUM_CYCLES CPU::opcode0x3B()
{
    dec16bit(&registers.sp);
    return 8;
} // DEC SP

// DAA INSTRUCTIONS
NUM_CYCLES CPU::opcode0x27()
{
    int a = registers.a;
    if (registers.flags.getFlag(FlagTypes::ADDSUB))
    {
        if (registers.flags.getFlag(FlagTypes::HALF_CARRY))
        {
            a = (a - 0x06) & 0xFF;
        }
        if (registers.flags.getFlag(FlagTypes::CARRY))
        {
            a -= 0x60;
        }
    } else {
        if (registers.flags.getFlag(FlagTypes::HALF_CARRY) || (a & 0x0F) > 9)
        {
            a += 0x06;
        }
        if (registers.flags.getFlag(FlagTypes::CARRY) || a > 0x9F)
        {
            a += 0x60;
        }
    }

    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    registers.flags.lowerFlag(FlagTypes::ZERO);

    if ((a & 0x100) == 0x100)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    a &= 0xFF;

    if (a == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }

    registers.a = a;

    return 4;
} // DAA

// CPL INSTRUCTIONS
NUM_CYCLES CPU::opcode0x2F()
{
    registers.a = ~registers.a;
    registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    registers.flags.raiseFlag(FlagTypes::ADDSUB);
    return 4;
} // CPL