// #include "instruction.h"
// #include <iostream>

// Instruction::Instruction(uint8_t opcode)
// {
//     // print in hex
//     std::cout << std::hex << (int)opcode << std::endl;
//     switch (opcode)
//     {        
//         case 0x87:
//             type = InstructionType::ADD;
//             target = RegisterTypes::A;
//             std::cout << "ADD A" << std::endl;
//             break;
//         case 0x80:
//             type = InstructionType::ADD;
//             target = RegisterTypes::B;
//             break;
//         case 0x81:
//             type = InstructionType::ADD;
//             target = RegisterTypes::C;
//             break;
//         case 0x82:
//             type = InstructionType::ADD;
//             target = RegisterTypes::D;
//             break;
//         case 0x83:
//             type = InstructionType::ADD;
//             target = RegisterTypes::E;
//             break;
//         case 0x84:
//             type = InstructionType::ADD;
//             target = RegisterTypes::H;
//             break;
//         case 0x85:
//             type = InstructionType::ADD;
//             target = RegisterTypes::L;
//             break;
//         case 0x86:
//             type = InstructionType::ADD;
//             target = RegisterTypes::HL;
//             break;
//         default:
//             throw std::invalid_argument("Invalid opcode");
//             break;
//     }
// }