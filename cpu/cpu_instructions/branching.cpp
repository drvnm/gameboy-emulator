#include "../cpu.h"
#include "../../common/defs.h"

#include <iostream>


void CPU::set16bitRegister(REGISTER *reg, uint16_t value)
{
}

NUM_CYCLES CPU::opcode0xC3()
{
    uint16_t address = load16BitFromPC();

    std::cout << "JUMP TO ADDRESS: " << std::hex << address << std::endl;

    registers.pc = address - 1;
    return 16;
} // JUMP TO ADDRESS

NUM_CYCLES CPU::opcode0xE9()
{
    registers.pc = registers.hl - 1; 
    return 4;
} // JUMP TO HL

NUM_CYCLES CPU::opcode0xC2()
{
    uint16_t address = load16BitFromPC();

    if (!registers.flags.zero)
    {
        registers.pc = address - 1;
        return 16;
    }
    registers.pc += 2; 
    return 12;
} // JUMP TO ADDRESS IF NOT ZERO

NUM_CYCLES CPU::opcode0xCA()
{
    uint16_t address = load16BitFromPC();

    if (registers.flags.zero)
    {
        registers.pc = address - 1;
        return 16;
    }
    registers.pc += 2;
    return 12;
} // JUMP TO ADDRESS IF ZERO

NUM_CYCLES CPU::opcode0xD2()
{
    uint16_t address = load16BitFromPC();

    if (!registers.flags.carry)
    {
        registers.pc = address - 1;
        return 16;
    }
    registers.pc += 2;
    return 12;
} // JUMP TO ADDRESS IF NOT CARRY

NUM_CYCLES CPU::opcode0xDA()
{
    uint16_t address = load16BitFromPC();

    if (registers.flags.carry)
    {
        registers.pc = address - 1;
        return 16;
    }
    registers.pc += 2;
    return 12;
} // JUMP TO ADDRESS IF CARRY

NUM_CYCLES CPU::opcode0x18()
{
    int8_t offset = memory[registers.pc + 1];
    registers.pc += offset - 1;
    return 12;
} // JUMP TO PC + n

NUM_CYCLES CPU::opcode0x20()
{
    int8_t offset = memory[registers.pc + 1];
    if (!registers.flags.zero)
    {
        registers.pc += offset - 1;
        return 12;
    }
    registers.pc += 1;
    return 8;
} // JUMP TO PC + n IF NOT ZERO

NUM_CYCLES CPU::opcode0x28()
{
    int8_t offset = memory[registers.pc + 1];
    if (registers.flags.zero)
    {
        registers.pc += offset - 1;
        return 12;
    }
    registers.pc += 1;
    return 8;
} // JUMP TO PC + n IF ZERO

NUM_CYCLES CPU::opcode0x30()
{
    int8_t offset = memory[registers.pc + 1];
    if (!registers.flags.carry)
    {
        registers.pc += offset - 1;
        return 12;
    }
    registers.pc += 1;
    return 8;
} // JUMP TO PC + n IF NOT CARRY

NUM_CYCLES CPU::opcode0x38()
{
    int8_t offset = memory[registers.pc + 1];
    if (registers.flags.carry)
    {
        registers.pc += offset - 1;
        return 12;
    }
    registers.pc += 1;
    return 8;
} // JUMP TO PC + n IF CARRY

// CALL INSTRUCTIONS
NUM_CYCLES CPU::opcode0xCD()
{
    uint16_t address = load16BitFromPC();

    push(registers.pc + 3);
    registers.pc = address - 1;
    return 24;
} // CALL ADDRESS

NUM_CYCLES CPU::opcode0xC4()
{
    uint16_t address = load16BitFromPC();

    if (!registers.flags.zero)
    {
        push(registers.pc + 3);
        registers.pc = address - 1;
        return 24;
    }
    registers.pc += 2;
    return 12;
} // CALL ADDRESS IF NOT ZERO

NUM_CYCLES CPU::opcode0xCC()
{
    uint16_t address = load16BitFromPC();

    if (registers.flags.zero)
    {
        push(registers.pc + 3);
        registers.pc = address - 1;
        return 24;
    }
    registers.pc += 2;
    return 12;
} // CALL ADDRESS IF ZERO

NUM_CYCLES CPU::opcode0xD4()
{
    uint16_t address = load16BitFromPC();

    if (!registers.flags.carry)
    {
        push(registers.pc +3);
        registers.pc = address - 1;
        return 24;
    }
    registers.pc += 2;
    return 12;
} // CALL ADDRESS IF NOT CARRY

NUM_CYCLES CPU::opcode0xDC()
{
    uint16_t address = load16BitFromPC();

    if (registers.flags.carry)
    {
        push(registers.pc + 3);
        registers.pc = address;
        return 24;
    }
    registers.pc += 2; 
    return 12;
} // CALL ADDRESS IF CARRY

// RETURN INSTRUCTIONS
NUM_CYCLES CPU::opcode0xC9()
{
    registers.pc = pop() - 1;
    return 16;
} // RETURN

NUM_CYCLES CPU::opcode0xC0()
{
    if (!registers.flags.zero)
    {
        registers.pc = pop() - 1;
        return 20;
    }
    return 8;
} // RETURN IF NOT ZERO

NUM_CYCLES CPU::opcode0xC8()
{
    if (registers.flags.zero)
    {
        registers.pc = pop() - 1;
        return 20;
    }
    return 8;
} // RETURN IF ZERO

NUM_CYCLES CPU::opcode0xD0()
{
    if (!registers.flags.carry)
    {
        registers.pc = pop() - 1;
        return 20;
    }
    return 8;
} // RETURN IF NOT CARRY

NUM_CYCLES CPU::opcode0xD8()
{
    if (registers.flags.carry)
    {
        registers.pc = pop() - 1;
        return 20;
    }
    return 8;
} // RETURN IF CARRY

// RESTART INSTRUCTIONS
NUM_CYCLES CPU::opcode0xC7()
{
    push(registers.pc);
    registers.pc = 0x00;
    return 16;
} // RESTART 0x00

NUM_CYCLES CPU::opcode0xCF()
{
    push(registers.pc);
    registers.pc = 0x08;
    return 16;
} // RESTART 0x08

NUM_CYCLES CPU::opcode0xD7()
{
    push(registers.pc);
    registers.pc = 0x10;
    return 16;
} // RESTART 0x10

NUM_CYCLES CPU::opcode0xDF()
{
    push(registers.pc);
    registers.pc = 0x18;
    return 16;
} // RESTART 0x18

NUM_CYCLES CPU::opcode0xE7()
{
    push(registers.pc);
    registers.pc = 0x20;
    return 16;
} // RESTART 0x20

NUM_CYCLES CPU::opcode0xEF()
{
    push(registers.pc);
    registers.pc = 0x28;
    return 16;
} // RESTART 0x28

NUM_CYCLES CPU::opcode0xF7()
{
    push(registers.pc);
    registers.pc = 0x30;
    return 16;
} // RESTART 0x30

NUM_CYCLES CPU::opcode0xFF()
{
    push(registers.pc);
    registers.pc = 0x38;
    return 16;
} // RESTART 0x38
