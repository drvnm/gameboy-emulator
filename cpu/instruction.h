// #pragma once

// #include <cstdint>
// #include <stdexcept>

// #include "../common/defs.h"
// #include "registers.h"

// enum InstructionType
// {
//     ADD,
// };

// // the instructions that are implemented on the Sharp LR35902
// class Instruction
// {
// private:
//     InstructionType type;
//     RegisterTypes target;

// public:
//     Instruction(InstructionType type, RegisterTypes target) : type(type), target(target) {}
//     Instruction(uint8_t opcode); // Decode opcode into instruction
//     InstructionType getType();
//     RegisterTypes getReg();
// };