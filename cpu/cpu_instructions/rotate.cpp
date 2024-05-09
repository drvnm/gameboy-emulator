#include "../CPU.h"

NUM_CYCLES CPU::opcode0x07()
{
    uint8_t bit = registers.a & 0x80;
    registers.a <<= 1;

    registers.flags.reset();

    if (bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
        registers.a = setBit(registers.a, 0);
    } else {
        registers.a = clearBit(registers.a, 0);
    }

    return 4;
} // RLCA

NUM_CYCLES CPU::opcode0x17()
{
    uint8_t bit = registers.a & 0x80;
    registers.a <<= 1;

    if(registers.flags.carry)
    {
        registers.a = setBit(registers.a, 0);
    } else {
        registers.a = clearBit(registers.a, 0);
    }

    registers.flags.reset();

    if (bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    return 4;
} // RLA

NUM_CYCLES CPU::opcode0x0F()
{
    uint8_t bit = registers.a & 0x01;
    registers.a >>= 1;

    registers.flags.reset();

    if (bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
        registers.a = setBit(registers.a, 7);
    } else {
        registers.a = clearBit(registers.a, 7);
    }

    return 4;
} // RRCA

NUM_CYCLES CPU::opcode0x1F()
{
    uint8_t bit = registers.a & 0x01;
    registers.a >>= 1;

    if(registers.flags.carry)
    {
        registers.a = setBit(registers.a, 7);
    } else {
        registers.a = clearBit(registers.a, 7);
    }

    registers.flags.reset();

    if (bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    return 4;
} // RRA

void CPU::rlc8bit(REGISTER *reg)
{
    uint8_t bit = *reg  & 0x80;
    *reg <<= 1;

    registers.flags.reset();

    if(bit) {
        registers.flags.raiseFlag(FlagTypes::CARRY);
        *reg = setBit(*reg, 0);
    } else {
        *reg = clearBit(*reg, 0);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x07()
{
    rlc8bit(&registers.a);
    return 8;
} // RLC A

NUM_CYCLES CPU::extendedOpcode0x00()
{
    rlc8bit(&registers.b);
    return 8;
} // RLC B

NUM_CYCLES CPU::extendedOpcode0x01()
{
    rlc8bit(&registers.c);
    return 8;
} // RLC C

NUM_CYCLES CPU::extendedOpcode0x02()
{
    rlc8bit(&registers.d);
    return 8;
} // RLC D

NUM_CYCLES CPU::extendedOpcode0x03()
{
    rlc8bit(&registers.e);
    return 8;
} // RLC E

NUM_CYCLES CPU::extendedOpcode0x04()
{
    rlc8bit(&registers.h);
    return 8;
} // RLC H

NUM_CYCLES CPU::extendedOpcode0x05()
{
    rlc8bit(&registers.l);
    return 8;
} // RLC L

NUM_CYCLES CPU::extendedOpcode0x06()
{
    uint8_t value = memory->readByte(registers.hl);
    rlc8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // RLC (HL)

void CPU::rrc8bit(REGISTER *reg)
{
    uint8_t bit = *reg & 0x01;
    *reg >>= 1;

    registers.flags.reset();

    if(bit) {
        registers.flags.raiseFlag(FlagTypes::CARRY);
        *reg = setBit(*reg, 7);
    } else {
        *reg = clearBit(*reg, 7);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x0F()
{
    rrc8bit(&registers.a);
    return 8;
} // RRC A

NUM_CYCLES CPU::extendedOpcode0x08()
{
    rrc8bit(&registers.b);
    return 8;
} // RRC B

NUM_CYCLES CPU::extendedOpcode0x09()
{
    rrc8bit(&registers.c);
    return 8;
} // RRC C

NUM_CYCLES CPU::extendedOpcode0x0A()
{
    rrc8bit(&registers.d);
    return 8;
} // RRC D

NUM_CYCLES CPU::extendedOpcode0x0B()
{
    rrc8bit(&registers.e);
    return 8;
} // RRC E

NUM_CYCLES CPU::extendedOpcode0x0C()
{
    rrc8bit(&registers.h);
    return 8;
} // RRC H

NUM_CYCLES CPU::extendedOpcode0x0D()
{
    rrc8bit(&registers.l);
    return 8;
} // RRC L

NUM_CYCLES CPU::extendedOpcode0x0E()
{
    uint8_t value = memory->readByte(registers.hl);
    rrc8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // RRC (HL)

void CPU::rl8bit(REGISTER *reg)
{
    uint8_t bit = *reg & 0x80;
    *reg <<= 1;

    if(registers.flags.carry)
    {
        *reg = setBit(*reg, 0);
    } else {
        *reg = clearBit(*reg, 0);
    }

    registers.flags.reset();

    if(bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x17()
{
    rl8bit(&registers.a);
    return 8;
} // RL A

NUM_CYCLES CPU::extendedOpcode0x10()
{
    rl8bit(&registers.b);
    return 8;
} // RL B

NUM_CYCLES CPU::extendedOpcode0x11()
{
    rl8bit(&registers.c);
    return 8;
} // RL C

NUM_CYCLES CPU::extendedOpcode0x12()
{
    rl8bit(&registers.d);
    return 8;
} // RL D

NUM_CYCLES CPU::extendedOpcode0x13()
{
    rl8bit(&registers.e);
    return 8;
} // RL E

NUM_CYCLES CPU::extendedOpcode0x14()
{
    rl8bit(&registers.h);
    return 8;
} // RL H

NUM_CYCLES CPU::extendedOpcode0x15()
{
    rl8bit(&registers.l);
    return 8;
} // RL L

NUM_CYCLES CPU::extendedOpcode0x16()
{
    uint8_t value = memory->readByte(registers.hl);
    rl8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // RL (HL)

void CPU::rr8bit(REGISTER *reg)
{
    uint8_t bit = *reg & 0x01;
    *reg >>= 1;

    if(registers.flags.carry)
    {
        *reg = setBit(*reg, 7);
    } else {
        *reg = clearBit(*reg, 7);
    }

    registers.flags.reset();

    if(bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x1F()
{
    rr8bit(&registers.a);
    return 8;
} // RR A

NUM_CYCLES CPU::extendedOpcode0x18()
{
    rr8bit(&registers.b);
    return 8;
} // RR B

NUM_CYCLES CPU::extendedOpcode0x19()
{
    rr8bit(&registers.c);
    return 8;
} // RR C

NUM_CYCLES CPU::extendedOpcode0x1A()
{
    rr8bit(&registers.d);
    return 8;
} // RR D

NUM_CYCLES CPU::extendedOpcode0x1B()
{
    rr8bit(&registers.e);
    return 8;
} // RR E

NUM_CYCLES CPU::extendedOpcode0x1C()
{
    rr8bit(&registers.h);
    return 8;
} // RR H

NUM_CYCLES CPU::extendedOpcode0x1D()
{
    rr8bit(&registers.l);
    return 8;
} // RR L

NUM_CYCLES CPU::extendedOpcode0x1E()
{
    uint8_t value = memory->readByte(registers.hl);
    rr8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // RR (HL)

void CPU::sla8bit(REGISTER *reg)
{
    uint8_t bit = *reg & 0x80;
    *reg <<= 1;

    registers.flags.reset();

    if(bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x27()
{
    sla8bit(&registers.a);
    return 8;
} // SLA A

NUM_CYCLES CPU::extendedOpcode0x20()
{
    sla8bit(&registers.b);
    return 8;
} // SLA B

NUM_CYCLES CPU::extendedOpcode0x21()
{
    sla8bit(&registers.c);
    return 8;
} // SLA C

NUM_CYCLES CPU::extendedOpcode0x22()
{
    sla8bit(&registers.d);
    return 8;
} // SLA D

NUM_CYCLES CPU::extendedOpcode0x23()
{
    sla8bit(&registers.e);
    return 8;
} // SLA E

NUM_CYCLES CPU::extendedOpcode0x24()
{
    sla8bit(&registers.h);
    return 8;
} // SLA H

NUM_CYCLES CPU::extendedOpcode0x25()
{
    sla8bit(&registers.l);
    return 8;
} // SLA L

NUM_CYCLES CPU::extendedOpcode0x26()
{
    uint8_t value = memory->readByte(registers.hl);
    sla8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // SLA (HL)

void CPU::sra8bit(REGISTER *reg)
{
    uint8_t firstBit = *reg & 0x01;
    uint8_t lastBit = *reg & 0x80;

    *reg >>= 1;

    if(lastBit)
    {
        *reg = setBit(*reg, 7);
    } else {
        *reg = clearBit(*reg, 7);
    }

    registers.flags.reset();

    if(firstBit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x2F()
{
    sra8bit(&registers.a);
    return 8;
} // SRA A

NUM_CYCLES CPU::extendedOpcode0x28()
{
    sra8bit(&registers.b);
    return 8;
} // SRA B

NUM_CYCLES CPU::extendedOpcode0x29()
{
    sra8bit(&registers.c);
    return 8;
} // SRA C

NUM_CYCLES CPU::extendedOpcode0x2A()
{
    sra8bit(&registers.d);
    return 8;
} // SRA D

NUM_CYCLES CPU::extendedOpcode0x2B()
{
    sra8bit(&registers.e);
    return 8;
} // SRA E

NUM_CYCLES CPU::extendedOpcode0x2C()
{
    sra8bit(&registers.h);
    return 8;
} // SRA H

NUM_CYCLES CPU::extendedOpcode0x2D()
{
    sra8bit(&registers.l);
    return 8;
} // SRA L

NUM_CYCLES CPU::extendedOpcode0x2E()
{
    uint8_t value = memory->readByte(registers.hl);
    sra8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // SRA (HL)

void CPU::srl8bit(REGISTER *reg)
{
    uint8_t bit = *reg & 0x01;
    *reg >>= 1;

    *reg = clearBit(*reg, 7);
    registers.flags.reset();

    if(bit)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x3F()
{
    srl8bit(&registers.a);
    return 8;
} // SRL A

NUM_CYCLES CPU::extendedOpcode0x38()
{
    srl8bit(&registers.b);
    return 8;
} // SRL B

NUM_CYCLES CPU::extendedOpcode0x39()
{
    srl8bit(&registers.c);
    return 8;
} // SRL C

NUM_CYCLES CPU::extendedOpcode0x3A()
{
    srl8bit(&registers.d);
    return 8;
} // SRL D

NUM_CYCLES CPU::extendedOpcode0x3B()
{
    srl8bit(&registers.e);
    return 8;
} // SRL E

NUM_CYCLES CPU::extendedOpcode0x3C()
{
    srl8bit(&registers.h);
    return 8;
} // SRL H

NUM_CYCLES CPU::extendedOpcode0x3D()
{
    srl8bit(&registers.l);
    return 8;
} // SRL L

NUM_CYCLES CPU::extendedOpcode0x3E()
{
    uint8_t value = memory->readByte(registers.hl);
    srl8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // SRL (HL)

void CPU::swap8bit(REGISTER *reg)
{
    registers.flags.reset();

    *reg = ((*reg & 0x0F) << 4) | ((*reg & 0xF0) >> 4);

    if(*reg == 0)
    {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    }
}

NUM_CYCLES CPU::extendedOpcode0x37()
{
    swap8bit(&registers.a);
    return 8;
} // SWAP A

NUM_CYCLES CPU::extendedOpcode0x30()
{
    swap8bit(&registers.b);
    return 8;
} // SWAP B

NUM_CYCLES CPU::extendedOpcode0x31()
{
    swap8bit(&registers.c);
    return 8;
} // SWAP C

NUM_CYCLES CPU::extendedOpcode0x32()
{
    swap8bit(&registers.d);
    return 8;
} // SWAP D

NUM_CYCLES CPU::extendedOpcode0x33()
{
    swap8bit(&registers.e);
    return 8;
} // SWAP E

NUM_CYCLES CPU::extendedOpcode0x34()
{
    swap8bit(&registers.h);
    return 8;
} // SWAP H

NUM_CYCLES CPU::extendedOpcode0x35()
{
    swap8bit(&registers.l);
    return 8;
} // SWAP L

NUM_CYCLES CPU::extendedOpcode0x36()
{
    uint8_t value = memory->readByte(registers.hl);
    swap8bit(&value);
    memory->writeByte(registers.hl, value);
    return 16;
} // SWAP (HL)


