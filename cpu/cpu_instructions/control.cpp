#include "../cpu.h"
#include "../../common/defs.h"
#include "../../memory/memory.h"

#include <stdexcept>

NUM_CYCLES CPU::opcode0x3F()
{
    if (registers.flags.getFlag(FlagTypes::CARRY))
    {
        registers.flags.lowerFlag(FlagTypes::CARRY);
    }
    else
    {
        registers.flags.raiseFlag(FlagTypes::CARRY);
    }
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
    registers.flags.lowerFlag(FlagTypes::HALF_CARRY);
    return 1;
} // CCF (C = !C)

NUM_CYCLES CPU::opcode0x37()
{
    registers.flags.raiseFlag(FlagTypes::CARRY);
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
    halted = true;
    return 1;
} // HALT

NUM_CYCLES CPU::opcode0x10()
{
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

