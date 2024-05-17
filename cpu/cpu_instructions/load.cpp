#include "../cpu.h"
#include "../../common/defs.h"
#include "../../memory/memory.h"

#include <iostream>

void CPU::load8bit(REGISTER *reg, uint8_t value)
{
    *reg = value;
}

NUM_CYCLES CPU::opcode0x7F()
{
    load8bit(&registers.a, registers.a);
    return 4;
} // LD A, AF.HIGH

NUM_CYCLES CPU::opcode0x78()
{
    load8bit(&registers.a, registers.b);
    return 4;
} // LD A, BC.HIGH

NUM_CYCLES CPU::opcode0x79()
{
    load8bit(&registers.a, registers.c);
    return 4;
} // LD A, BC.LOW

NUM_CYCLES CPU::opcode0x7A()
{
    load8bit(&registers.a, registers.d);
    return 4;
} // LD A, DE.HIGH

NUM_CYCLES CPU::opcode0x7B()
{
    load8bit(&registers.a, registers.e);
    return 4;
} // LD A, DE.LOW

NUM_CYCLES CPU::opcode0x7C()
{
    load8bit(&registers.a, registers.h);
    return 4;
} // LD A, HL.HIGH

NUM_CYCLES CPU::opcode0x7D()
{
    load8bit(&registers.a, registers.l);
    return 4;
} // LD A, HL.LOW

NUM_CYCLES CPU::opcode0x7E()
{
    load8bit(&registers.a, memory->readByte(registers.hl));
    return 8;
} // LD A, (HL)

NUM_CYCLES CPU::opcode0x3E()
{
    load8bit(&registers.a, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD A, NUMBER

NUM_CYCLES CPU::opcode0x47()
{
    load8bit(&registers.b, registers.a);
    return 4;
} // LD B, AF.HIGH

NUM_CYCLES CPU::opcode0x40()
{
    load8bit(&registers.b, registers.b);
    return 4;
} // LD B, BC.HIGH

NUM_CYCLES CPU::opcode0x41()
{
    load8bit(&registers.b, registers.c);
    return 4;
} // LD B, BC.LOW

NUM_CYCLES CPU::opcode0x42()
{
    load8bit(&registers.b, registers.d);
    return 4;
} // LD B, DE.HIGH

NUM_CYCLES CPU::opcode0x43()
{
    load8bit(&registers.b, registers.e);
    return 4;
} // LD B, DE.LOW

NUM_CYCLES CPU::opcode0x44()
{
    load8bit(&registers.b, registers.h);
    return 4;
} // LD B, HL.HIGH

NUM_CYCLES CPU::opcode0x45()
{
    load8bit(&registers.b, registers.l);
    return 4;
} // LD B, HL.LOW

NUM_CYCLES CPU::opcode0x46()
{
    load8bit(&registers.b, memory->readByte(registers.hl));
    return 8;
} // LD B, (HL)

NUM_CYCLES CPU::opcode0x06()
{
    load8bit(&registers.b, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD B, NUMBER

NUM_CYCLES CPU::opcode0x4F()
{
    load8bit(&registers.c, registers.a);
    return 4;
} // LD C, AF.HIGH

NUM_CYCLES CPU::opcode0x48()
{
    load8bit(&registers.c, registers.b);
    return 4;
} // LD C, BC.HIGH

NUM_CYCLES CPU::opcode0x49()
{
    load8bit(&registers.c, registers.c);
    return 4;
} // LD C, BC.LOW

NUM_CYCLES CPU::opcode0x4A()
{
    load8bit(&registers.c, registers.d);
    return 4;
} // LD C, DE.HIGH

NUM_CYCLES CPU::opcode0x4B()
{
    load8bit(&registers.c, registers.e);
    return 4;
} // LD C, DE.LOW

NUM_CYCLES CPU::opcode0x4C()
{
    load8bit(&registers.c, registers.h);
    return 4;
} // LD C, HL.HIGH

NUM_CYCLES CPU::opcode0x4D()
{
    load8bit(&registers.c, registers.l);
    return 4;
} // LD C, HL.LOW

NUM_CYCLES CPU::opcode0x4E()
{
    load8bit(&registers.c, memory->readByte(registers.hl));
    return 8;
} // LD C, (HL)

NUM_CYCLES CPU::opcode0x0E()
{
    load8bit(&registers.c, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD C, NUMBER

NUM_CYCLES CPU::opcode0x57()
{
    load8bit(&registers.d, registers.a);
    return 4;
} // LD D, AF.HIGH

NUM_CYCLES CPU::opcode0x50()
{
    load8bit(&registers.d, registers.b);
    return 4;
} // LD D, BC.HIGH

NUM_CYCLES CPU::opcode0x51()
{
    load8bit(&registers.d, registers.c);
    return 4;
} // LD D, BC.LOW

NUM_CYCLES CPU::opcode0x52()
{
    load8bit(&registers.d, registers.d);
    return 4;
} // LD D, DE.HIGH

NUM_CYCLES CPU::opcode0x53()
{
    load8bit(&registers.d, registers.e);
    return 4;
} // LD D, DE.LOW

NUM_CYCLES CPU::opcode0x54()
{
    load8bit(&registers.d, registers.h);
    return 4;
} // LD D, HL.HIGH

NUM_CYCLES CPU::opcode0x55()
{
    load8bit(&registers.d, registers.l);
    return 4;
} // LD D, HL.LOW

NUM_CYCLES CPU::opcode0x56()
{
    load8bit(&registers.d, memory->readByte(registers.hl));
    return 8;
} // LD D, (HL)

NUM_CYCLES CPU::opcode0x16()
{
    load8bit(&registers.d, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD D, NUMBER

NUM_CYCLES CPU::opcode0x5F()
{
    load8bit(&registers.e, registers.a);
    return 4;
} // LD E, AF.HIGH

NUM_CYCLES CPU::opcode0x58()
{
    load8bit(&registers.e, registers.b);
    return 4;
} // LD E, BC.HIGH

NUM_CYCLES CPU::opcode0x59()
{
    load8bit(&registers.e, registers.c);
    return 4;
} // LD E, BC.LOW

NUM_CYCLES CPU::opcode0x5A()
{
    load8bit(&registers.e, registers.d);
    return 4;
} // LD E, DE.HIGH

NUM_CYCLES CPU::opcode0x5B()
{
    load8bit(&registers.e, registers.e);
    return 4;
} // LD E, DE.LOW

NUM_CYCLES CPU::opcode0x5C()
{
    load8bit(&registers.e, registers.h);
    return 4;
} // LD E, HL.HIGH

NUM_CYCLES CPU::opcode0x5D()
{
    load8bit(&registers.e, registers.l);
    return 4;
} // LD E, HL.LOW

NUM_CYCLES CPU::opcode0x5E()
{
    load8bit(&registers.e, memory->readByte(registers.hl));
    return 8;
} // LD E, (HL)

NUM_CYCLES CPU::opcode0x1E()
{
    load8bit(&registers.e, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD E, NUMBER

NUM_CYCLES CPU::opcode0x67()
{
    load8bit(&registers.h, registers.a);
    return 4;
} // LD H, AF.HIGH

NUM_CYCLES CPU::opcode0x60()
{
    load8bit(&registers.h, registers.b);
    return 4;
} // LD H, BC.HIGH

NUM_CYCLES CPU::opcode0x61()
{
    load8bit(&registers.h, registers.c);
    return 4;
} // LD H, BC.LOW

NUM_CYCLES CPU::opcode0x62()
{
    load8bit(&registers.h, registers.d);
    return 4;
} // LD H, DE.HIGH

NUM_CYCLES CPU::opcode0x63()
{
    load8bit(&registers.h, registers.e);
    return 4;
} // LD H, DE.LOW

NUM_CYCLES CPU::opcode0x64()
{
    load8bit(&registers.h, registers.h);
    return 4;
} // LD H, HL.HIGH

NUM_CYCLES CPU::opcode0x65()
{
    load8bit(&registers.h, registers.l);
    return 4;
} // LD H, HL.LOW

NUM_CYCLES CPU::opcode0x66()
{
    load8bit(&registers.h, memory->readByte(registers.hl));
    return 8;
} // LD H, (HL)

NUM_CYCLES CPU::opcode0x26()
{
    load8bit(&registers.h, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD H, NUMBER

NUM_CYCLES CPU::opcode0x6F()
{
    load8bit(&registers.l, registers.a);
    return 4;
} // LD L, AF.HIGH

NUM_CYCLES CPU::opcode0x68()
{
    load8bit(&registers.l, registers.b);
    return 4;
} // LD L, BC.HIGH

NUM_CYCLES CPU::opcode0x69()
{
    load8bit(&registers.l, registers.c);
    return 4;
} // LD L, BC.LOW

NUM_CYCLES CPU::opcode0x6A()
{
    load8bit(&registers.l, registers.d);
    return 4;
} // LD L, DE.HIGH

NUM_CYCLES CPU::opcode0x6B()
{
    load8bit(&registers.l, registers.e);
    return 4;
} // LD L, DE.LOW

NUM_CYCLES CPU::opcode0x6C()
{
    load8bit(&registers.l, registers.h);
    return 4;
} // LD L, HL.HIGH

NUM_CYCLES CPU::opcode0x6D()
{
    load8bit(&registers.l, registers.l);
    return 4;
} // LD L, HL.LOW

NUM_CYCLES CPU::opcode0x6E()
{
    load8bit(&registers.l, memory->readByte(registers.hl));
    return 8;
} // LD L, (HL)

NUM_CYCLES CPU::opcode0x2E()
{
    load8bit(&registers.l, memory->readByte(registers.pc + 1));
    registers.pc += 1;
    return 8;
} // LD L, NUMBER

NUM_CYCLES CPU::opcode0x77()
{
    memory->writeByte(registers.hl, registers.a);
    return 8;
} // LD (HL), AF.HIGH

NUM_CYCLES CPU::opcode0x70()
{
    memory->writeByte(registers.hl, registers.b);
    return 8;
} // LD (HL), BC.HIGH

NUM_CYCLES CPU::opcode0x71()
{
    memory->writeByte(registers.hl, registers.c);
    return 8;
} // LD (HL), BC.LOW

NUM_CYCLES CPU::opcode0x72()
{
    memory->writeByte(registers.hl, registers.d);
    return 8;
} // LD (HL), DE.HIGH

NUM_CYCLES CPU::opcode0x73()
{
    memory->writeByte(registers.hl, registers.e);
    return 8;
} // LD (HL), DE.LOW

NUM_CYCLES CPU::opcode0x74()
{
    memory->writeByte(registers.hl, registers.h);
    return 8;
} // LD (HL), HL.HIGH

NUM_CYCLES CPU::opcode0x75()
{
    memory->writeByte(registers.hl, registers.l);
    return 8;
} // LD (HL), HL.LOW

NUM_CYCLES CPU::opcode0x36()
{
    registers.pc += 1;
    memory->writeByte(registers.hl, memory->readByte(registers.pc));
    return 12;
} // LD (HL), NUMBER

NUM_CYCLES CPU::opcode0x0A()
{
    load8bit(&registers.a, memory->readByte(registers.bc));
    return 8;
} // LD A, (BC)

NUM_CYCLES CPU::opcode0x1A()
{
    load8bit(&registers.a, memory->readByte(registers.de));
    return 8;
} // LD A, (DE)

NUM_CYCLES CPU::opcode0xFA()
{
    uint16_t val = load16BitFromPC();
    load8bit(&registers.a, memory->readByte(val));
    registers.pc += 2;
    return 16;
} // LD A, (NUMBER)

NUM_CYCLES CPU::opcode0x02()
{
    memory->writeByte(registers.bc, registers.a);
    return 8;
} // LD (BC), A

NUM_CYCLES CPU::opcode0x12()
{
    // print the value of registers.de
    memory->writeByte(registers.de, registers.a);
    return 8;
} // LD (DE), A

NUM_CYCLES CPU::opcode0xEA()
{
    uint16_t val = load16BitFromPC();
    memory->writeByte(val, registers.a);
    registers.pc += 2;
    return 16;
} // LD (NUMBER), A

NUM_CYCLES CPU::opcode0xF0()
{
    registers.pc += 1;
    load8bit(&registers.a, memory->readByte(0xFF00 + memory->readByte(registers.pc)));
    return 12;
} // LD A, (C) (0xFF00 + n)

NUM_CYCLES CPU::opcode0xE0()
{
    registers.pc += 1;
    memory->writeByte(0xFF00 + memory->readByte(registers.pc), registers.a);
    return 12;
} // LD (C), A (0xFF00 + n)

NUM_CYCLES CPU::opcode0xF2()
{
    load8bit(&registers.a, memory->readByte(0xFF00 + registers.c));
    return 8;
} // LD A, (C) (0xFF00 + C)

NUM_CYCLES CPU::opcode0xE2()
{
    memory->writeByte(0xFF00 + registers.c, registers.a);
    return 8;
} // LD (C), A (0xFF00 + C)

NUM_CYCLES CPU::opcode0x3A()
{
    load8bit(&registers.a, memory->readByte(registers.hl));
    registers.hl--;
    return 8;
} // LDD A, (HL)

NUM_CYCLES CPU::opcode0x32()
{
    memory->writeByte(registers.hl, registers.a);
    registers.hl--;
    return 8;
} // LDD (HL), A

NUM_CYCLES CPU::opcode0x2A()
{
    load8bit(&registers.a, memory->readByte(registers.hl));
    registers.hl++;
    return 8;
} // LDI A, (HL)

NUM_CYCLES CPU::opcode0x22()
{
    memory->writeByte(registers.hl, registers.a);
    registers.hl++;
    return 8;
} // LDI (HL), A

// 16-BIT LOAD INSTRUCTIONS
void CPU::load16bit(REGISTER16 *reg, uint16_t value)
{
    *reg = value;
}

NUM_CYCLES CPU::opcode0x01()
{
    uint16_t value = load16BitFromPC();
    load16bit(&registers.bc, value);
    registers.pc += 2;
    return 12;
} // LD BC, NUMBER

NUM_CYCLES CPU::opcode0x11()
{
    uint16_t value = load16BitFromPC();

    load16bit(&registers.de, value);
    registers.pc += 2;
    return 12;
} // LD DE, NUMBER

NUM_CYCLES CPU::opcode0x21()
{
    uint16_t value = load16BitFromPC();

    load16bit(&registers.hl, value);
    registers.pc += 2;
    return 12;
} // LD HL, NUMBER

NUM_CYCLES CPU::opcode0x31()
{
    uint16_t value = load16BitFromPC();

    load16bit(&registers.sp, value);
    registers.pc += 2;
    return 12;
} // LD SP, NUMBER

NUM_CYCLES CPU::opcode0xF9()
{
    load16bit(&registers.sp, registers.hl);
    return 8;
} // LD SP, HL

NUM_CYCLES CPU::opcode0xF8()
{
    int8_t offset = memory->readByte(registers.pc + 1);
    uint16_t result = registers.sp + offset;

    registers.flags.reset();

    if (((registers.sp ^ offset ^ result) & 0x100) == 0x100)
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }   

    if (((registers.sp ^ offset ^ result) & 0x10) == 0x10)
    {
        registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    }
    registers.hl = result;
    registers.pc += 1;

    return 12;
} // LD HL, SP + n

NUM_CYCLES CPU::opcode0x08()
{
    uint16_t address = load16BitFromPC();
    memory->writeByte(address, registers.sp & 0xFF);
    memory->writeByte(address + 1, registers.sp >> 8);
    registers.pc += 2;
    return 20;
} // LD (NUMBER), SP

// PUSH AND POP INSTRUCTIONS
NUM_CYCLES CPU::opcode0xF5()
{
    push(registers.af);
    return 16;
} // PUSH AF

NUM_CYCLES CPU::opcode0xC5()
{
    push(registers.bc);
    return 16;
} // PUSH BC

NUM_CYCLES CPU::opcode0xD5()
{
    push(registers.de);
    return 16;
} // PUSH DE

NUM_CYCLES CPU::opcode0xE5()
{
    push(registers.hl);
    return 16;
} // PUSH HL

NUM_CYCLES CPU::opcode0xF1()
{
    registers.af = pop();
    registers.f &= 0xF0;
    return 12;
} // POP AF

NUM_CYCLES CPU::opcode0xC1()
{
    registers.bc = pop();
    return 12;
} // POP BC

NUM_CYCLES CPU::opcode0xD1()
{
    registers.de = pop();
    return 12;
} // POP DE

NUM_CYCLES CPU::opcode0xE1()
{
    registers.hl = pop();
    return 12;
} // POP HL
