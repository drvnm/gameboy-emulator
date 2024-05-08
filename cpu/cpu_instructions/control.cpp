#include "../cpu.h"
#include "../../common/defs.h"
#include <stdexcept>

NUM_CYCLES CPU::opcode0x3F()
{
    registers.flags.carry ^= 1;
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    return 1;
} // CCF (C = !C)

NUM_CYCLES CPU::opcode0x37()
{
    registers.flags.carry = 1;
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    return 1;
} // SCF (C = 1)

NUM_CYCLES CPU::opcode0x00()
{
    return 1;
} // NOP

NUM_CYCLES CPU::opcode0x76()
{
    throw std::runtime_error("HALT instruction not implemented");
    return 1;
} // HALT

NUM_CYCLES CPU::opcode0x10()
{
    throw std::runtime_error("STOP instruction not implemented");
    return 1;
} // STOP

NUM_CYCLES CPU::opcode0xF3()
{
    registers.ime = false;
    return 1;
} // DI (Disable interrupts)

NUM_CYCLES CPU::opcode0xFB()
{
    registers.ime = true;
    return 1;
} // EI