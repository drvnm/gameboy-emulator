#include "../CPU.h"

////////////////////////////////////////// BIT

/*!
 Method that checks a specific bit from a register.
 If the bit checked is set, then the zero flag is raised and cleared otherwise.
 The half carry flag is raised and the add sub flag cleared.
*/
void CPU::bit(REGISTER* reg, uint8_t position) {
    if ( bitIsSet(*reg, position) ) {
        registers.flags.lowerFlag(FlagTypes::ZERO);
    } else {
        registers.flags.raiseFlag(FlagTypes::ZERO);
    
    }
    registers.flags.raiseFlag(FlagTypes::HALF_CARRY);
    registers.flags.lowerFlag(FlagTypes::ADDSUB);
}

NUM_CYCLES CPU::opcode0x40() {
    bit(&registers.b, 0);
    return 8;
}// bit 0, B

NUM_CYCLES CPU::opcode0x41() {
    bit(&registers.c, 0);
    return 8;
}// bit 0, C

NUM_CYCLES CPU::opcode0x42() {
    bit(&registers.d, 0);
    return 8;
}// bit 0, D

NUM_CYCLES CPU::opcode0x43() {
    bit(&registers.e, 0);
    return 8;
}// bit 0, E

NUM_CYCLES CPU::opcode0x44() {
    bit(&registers.h, 0);
    return 8;
}// bit 0, H

NUM_CYCLES CPU::opcode0x45() {
    bit(&registers.l, 0);
    return 8;
}// bit 0, L

NUM_CYCLES CPU::opcode0x46() {
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 0);
    return 12;
}// bit 0, (HL)

NUM_CYCLES CPU::opcode0x47() {
    bit(&registers.a, 0);
    return 8;
}// bit 0, A


NUM_CYCLES CPU::opcode0x48() {
    bit(&registers.b, 1);
    return 8;
}// bit 1, B

NUM_CYCLES CPU::opcode0x49() {
    bit(&registers.c, 1);
    return 8;
}// bit 1, C

NUM_CYCLES CPU::opcode0x4A() {
    bit(&registers.d, 1);
    return 8;
}// bit 1, D

NUM_CYCLES CPU::opcode0x4B() {
    bit(&registers.e, 1);
    return 8;
}// bit 1, E

NUM_CYCLES CPU::opcode0x4C() {
    bit(&registers.h, 1);
    return 8;
}// bit 1, H

NUM_CYCLES CPU::opcode0x4D() {
    bit(&registers.l, 1);
    return 8;
}// bit 1, L

NUM_CYCLES CPU::opcode0x4E() {
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 1);
    return 12;
}// bit 1, (HL)

NUM_CYCLES CPU::opcode0x4F() {
    bit(&registers.a, 1);
    return 8;
}// bit 1, A


NUM_CYCLES CPU::opcode0x50() {
    bit(&registers.b, 2);
    return 8;
}// bit 2, B

NUM_CYCLES CPU::opcode0x51() {
    bit(&registers.c, 2);
    return 8;
}// bit 2, C

NUM_CYCLES CPU::opcode0x52() {
    bit(&registers.d, 2);
    return 8;
}// bit 2, D

NUM_CYCLES CPU::opcode0x53() {
    bit(&registers.e, 2);
    return 8;
}// bit 2, E

NUM_CYCLES CPU::opcode0x54() {
    bit(&registers.h, 2);
    return 8;
}// bit 2, H

NUM_CYCLES CPU::opcode0x55() {
    bit(&registers.l, 2);
    return 8;
}// bit 2, L

NUM_CYCLES CPU::opcode0x56() {
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 2);
    return 12;
}// bit 2, (HL)

NUM_CYCLES CPU::opcode0x57() {
    bit(&registers.a, 2);
    return 8;
}// bit 2, A


NUM_CYCLES CPU::opcode0x58() {
    bit(&registers.b, 3);
    return 8;
}// bit 3, B

NUM_CYCLES CPU::opcode0x59() {
    bit(&registers.c, 3);
    return 8;
}// bit 3, C

NUM_CYCLES CPU::opcode0x5A() {
    bit(&registers.d, 3);
    return 8;
}// bit 3, D

NUM_CYCLES CPU::opcode0x5B() {
    bit(&registers.e, 3);
    return 8;
}// bit 3, E

NUM_CYCLES CPU::opcode0x5C() {
    bit(&registers.h, 3);
    return 8;
}// bit 3, H

NUM_CYCLES CPU::opcode0x5D() {
    bit(&registers.l, 3);
    return 8;
}// bit 3, L

NUM_CYCLES CPU::opcode0x5E() {
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 3);
    return 12;
}// bit 3, (HL)

NUM_CYCLES CPU::opcode0x5F() {
    bit(&registers.a, 3);
    return 8;
}// bit 3, A


NUM_CYCLES CPU::opcode0x60() {
    bit(&registers.b, 4);
    return 8;
}// bit 4, B

NUM_CYCLES CPU::opcode0x61() {
    bit(&registers.c, 4);
    return 8;
}// bit 4, C

NUM_CYCLES CPU::opcode0x62() {
    bit(&registers.d, 4);
    return 8;
}// bit 4, D

NUM_CYCLES CPU::opcode0x63() {
    bit(&registers.e, 4);
    return 8;
}// bit 4, E

NUM_CYCLES CPU::opcode0x64() {
    bit(&registers.h, 4);
    return 8;
}// bit 4, H

NUM_CYCLES CPU::opcode0x65() {
    bit(&registers.l, 4);
    return 8;
}// bit 4, L

NUM_CYCLES CPU::opcode0x66() {
    uint8_t data = memory->readByte(registers.hl);
    bit(&data, 4);
    return 12;
}// bit 4, (HL)

NUM_CYCLES CPU::opcode0x67() {
    bit(&registers.a, 4);
    return 8;
}// bit 4, A


NUM_CYCLES CPU::opcode0x68() {
    bit(&registers.b, 5);
    return 8;
}// bit 5, B

NUM_CYCLES CPU::opcode0x69() {
    return 8;
}// bit 5, C

NUM_CYCLES CPU::opcode0x6A() {
    return 8;
}// bit 5, D

NUM_CYCLES CPU::opcode0x6B() {
    return 8;
}// bit 5, E

NUM_CYCLES CPU::opcode0x6C() {
    return 8;
}// bit 5, H

NUM_CYCLES CPU::opcode0x6D() {
    return 8;
}// bit 5, L

NUM_CYCLES CPU::opcode0x6E() {
    return 12;
}// bit 5, (HL)

NUM_CYCLES CPU::opcode0x6F() {
    return 8;
}// bit 5, A


NUM_CYCLES CPU::opcode0x70() {
    return 8;
}// bit 6, B

NUM_CYCLES CPU::opcode0x71() {
    return 8;
}// bit 6, C

NUM_CYCLES CPU::opcode0x72() {
    return 8;
}// bit 6, D

NUM_CYCLES CPU::opcode0x73() {
    return 8;
}// bit 6, E

NUM_CYCLES CPU::opcode0x74() {
    return 8;
}// bit 6, H

NUM_CYCLES CPU::opcode0x75() {
    return 8;
}// bit 6, L

NUM_CYCLES CPU::opcode0x76() {
    return 12;
}// bit 6, (HL)

NUM_CYCLES CPU::opcode0x77() {
    return 8;
}// bit 6, A


NUM_CYCLES CPU::opcode0x78() {
    return 8;
}// bit 7, B

NUM_CYCLES CPU::opcode0x79() {
    return 8;
}// bit 7, C

NUM_CYCLES CPU::opcode0x7A() {
    return 8;
}// bit 7, D

NUM_CYCLES CPU::opcode0x7B() {
    return 8;
}// bit 7, E

NUM_CYCLES CPU::opcode0x7C() {
    return 8;
}// bit 7, H

NUM_CYCLES CPU::opcode0x7D() {
    return 8;
}// bit 7, L

NUM_CYCLES CPU::opcode0x7E() {
    return 12;
}// bit 7, (HL)

NUM_CYCLES CPU::opcode0x7F() {
    return 8;
}// bit 7, A

//////////////////////////////////////// RES

/*!
 Method that reset a specific bit from a register.
 */
void CPU::res(REGISTER *reg, uint8_t position) {
    
}

NUM_CYCLES CPU::opcode0x80() {
    return 8;
}// res 0, B

NUM_CYCLES CPU::opcode0x81() {
    return 8;
}// res 0, C

NUM_CYCLES CPU::opcode0x82() {
    return 8;
}// res 0, D

NUM_CYCLES CPU::opcode0x83() {
    return 8;
}// res 0, E

NUM_CYCLES CPU::opcode0x84() {
    return 8;
}// res 0, H

NUM_CYCLES CPU::opcode0x85() {
    return 8;
}// res 0, L

NUM_CYCLES CPU::opcode0x86() {
    return 16;
}// res 0, (HL)

NUM_CYCLES CPU::opcode0x87() {
    return 8;
}// res 0, A


NUM_CYCLES CPU::opcode0x88() {
    return 8;
}// res 1, B

NUM_CYCLES CPU::opcode0x89() {
    return 8;
}// res 1, C

NUM_CYCLES CPU::opcode0x8A() {
    return 8;
}// res 1, D

NUM_CYCLES CPU::opcode0x8B() {
    return 8;
}// res 1, E

NUM_CYCLES CPU::opcode0x8C() {
    return 8;
}// res 1, H

NUM_CYCLES CPU::opcode0x8D() {
    return 8;
}// res 1, L

NUM_CYCLES CPU::opcode0x8E() {
    return 16;
}// res 1, (HL)

NUM_CYCLES CPU::opcode0x8F() {
    return 8;
}// res 1, A


NUM_CYCLES CPU::opcode0x90() {
    return 8;
}// res 2, B

NUM_CYCLES CPU::opcode0x91() {
    return 8;
}// res 2, C

NUM_CYCLES CPU::opcode0x92() {
    return 8;
}// res 2, D

NUM_CYCLES CPU::opcode0x93() {
    return 8;
}// res 2, E

NUM_CYCLES CPU::opcode0x94() {
    return 8; // res 2, H
}

NUM_CYCLES CPU::opcode0x95() {
    return 8;
}// res 2, L

NUM_CYCLES CPU::opcode0x96() {
    return 16;
}// res 2, (HL)

NUM_CYCLES CPU::opcode0x97() {
    return 8;
}// res 2, A


NUM_CYCLES CPU::opcode0x98() {
    return 8;
}// res 3, B

NUM_CYCLES CPU::opcode0x99() {
    return 8;
}// res 3, C

NUM_CYCLES CPU::opcode0x9A() {
    return 8;
}// res 3, D

NUM_CYCLES CPU::opcode0x9B() {
    return 8;
}// res 3, E

NUM_CYCLES CPU::opcode0x9C() {
    return 8;
}// res 3, H

NUM_CYCLES CPU::opcode0x9D() {
    return 8;
}// res 3, L

NUM_CYCLES CPU::opcode0x9E() {
   return 16;
}// res 3, (HL)

NUM_CYCLES CPU::opcode0x9F() {
    return 8;
}// res 3, A


NUM_CYCLES CPU::opcode0xA0() {
    return 8;
}// res 4, B

NUM_CYCLES CPU::opcode0xA1() {
    return 8;
}// res 4, C

NUM_CYCLES CPU::opcode0xA2() {
    return 8;
}// res 4, D

NUM_CYCLES CPU::opcode0xA3() {
    return 8;
}// res 4, E

NUM_CYCLES CPU::opcode0xA4() {
    return 8;
}// res 4, H

NUM_CYCLES CPU::opcode0xA5() {
    return 8;
}// res 4, L

NUM_CYCLES CPU::opcode0xA6() {

    return 16;
}// res 4, (HL)

NUM_CYCLES CPU::opcode0xA7() {

    return 8;
}// res 4, A


NUM_CYCLES CPU::opcode0xA8() {
    return 8;
}// res 5, B

NUM_CYCLES CPU::opcode0xA9() {

    return 8;
}// res 5, C

NUM_CYCLES CPU::opcode0xAA() {

    return 8;
}// res 5, D

NUM_CYCLES CPU::opcode0xAB() {
    return 8;
}// res 5, E

NUM_CYCLES CPU::opcode0xAC() {

    return 8;
}// res 5, H

NUM_CYCLES CPU::opcode0xAD() {

    return 8;
}// res 5, L

NUM_CYCLES CPU::opcode0xAE() {

    return 16;
}// res 5, (HL)

NUM_CYCLES CPU::opcode0xAF() {

    return 8;
}// res 5, A


NUM_CYCLES CPU::opcode0xB0() {

    return 8;
}// res 6, B

NUM_CYCLES CPU::opcode0xB1() {

    return 8;
}// res 6, C

NUM_CYCLES CPU::opcode0xB2() {

    return 8;
}// res 6, D

NUM_CYCLES CPU::opcode0xB3() {

    return 8;
}// res 6, E

NUM_CYCLES CPU::opcode0xB4() {

    return 8;
}// res 6, H

NUM_CYCLES CPU::opcode0xB5() {

    return 8;
}// res 6, L

NUM_CYCLES CPU::opcode0xB6() {

    return 16;
}// res 6, (HL)

NUM_CYCLES CPU::opcode0xB7() {

    return 8;
}// res 6, A


NUM_CYCLES CPU::opcode0xB8() {

    return 8;
}// res 7, B

NUM_CYCLES CPU::opcode0xB9() {

    return 8;
}// res 7, C

NUM_CYCLES CPU::opcode0xBA() {

    return 8;
}// res 7, D

NUM_CYCLES CPU::opcode0xBB() {

    return 8;
}// res 7, E

NUM_CYCLES CPU::opcode0xBC() {

    return 8;
}// res 7, H

NUM_CYCLES CPU::opcode0xBD() {

    return 8;
}// res 7, L

NUM_CYCLES CPU::opcode0xBE() {

    return 16;
}// res 7, (HL)

NUM_CYCLES CPU::opcode0xBF() {
    return 8;
}// res 7, A

//////////////////////////////////////// SET

/*!
 Method that sets a specific bit from a register.
 */
void CPU::set(REGISTER * reg, uint8_t position) {
}

NUM_CYCLES CPU::opcode0xC0() {
    return 8;
}// set 0, B

NUM_CYCLES CPU::opcode0xC1() {

    return 8;
}// set 0, C

NUM_CYCLES CPU::opcode0xC2() {
    return 8;
}// set 0, D

NUM_CYCLES CPU::opcode0xC3() {

    return 8;
}// set 0, E

NUM_CYCLES CPU::opcode0xC4() {

    return 8;
}// set 0, H

NUM_CYCLES CPU::opcode0xC5() {

    return 8;
}// set 0, L

NUM_CYCLES CPU::opcode0xC6() {

    return 16;
}// set 0, (HL)

NUM_CYCLES CPU::opcode0xC7() {

    return 8;
}// set 0, A


NUM_CYCLES CPU::opcode0xC8() {
 
    return 8;
}// set 1, B

NUM_CYCLES CPU::opcode0xC9() {
 
    return 8;
}// set 1, C

NUM_CYCLES CPU::opcode0xCA() {
 
    return 8;
}// set 1, D

NUM_CYCLES CPU::opcode0xCB() {
    return 8;
}// set 1, E

NUM_CYCLES CPU::opcode0xCC() {
 
    return 8;
}// set 1, H

NUM_CYCLES CPU::opcode0xCD() {

    return 8;
}// set 1, L

NUM_CYCLES CPU::opcode0xCE() {

    return 16;
}// set 1, (HL)

NUM_CYCLES CPU::opcode0xCF() {
 
    return 8;
}// set 1, A


NUM_CYCLES CPU::opcode0xD0() {

    return 8;
}// set 2, B

NUM_CYCLES CPU::opcode0xD1() {

    return 8;
}// set 2, C

NUM_CYCLES CPU::opcode0xD2() {

    return 8;
}// set 2, D

NUM_CYCLES CPU::opcode0xD3() {

    return 8;
}// set 2, E

NUM_CYCLES CPU::opcode0xD4() {
    return 8;
}// set 2, H

NUM_CYCLES CPU::opcode0xD5() {
    return 8;
}// set 2, L

NUM_CYCLES CPU::opcode0xD6() {

    return 16;
}// set 2, (HL)

NUM_CYCLES CPU::opcode0xD7() {

    return 8;
}// set 2, A


NUM_CYCLES CPU::opcode0xD8() {

    return 8;
}// set 3, B

NUM_CYCLES CPU::opcode0xD9() {

    return 8;
}// set 3, C

NUM_CYCLES CPU::opcode0xDA() {

    return 8;
}// set 3, D

NUM_CYCLES CPU::opcode0xDB() {

    return 8;
}// set 3, E

NUM_CYCLES CPU::opcode0xDC() {

    return 8;
}// set 3, H

NUM_CYCLES CPU::opcode0xDD() {

    return 8;
}// set 3, L

NUM_CYCLES CPU::opcode0xDE() {

    return 16;
}// set 3, (HL)

NUM_CYCLES CPU::opcode0xDF() {

    return 8;
}// set 3, A


NUM_CYCLES CPU::opcode0xE0() {

    return 8;
}// set 4, B

NUM_CYCLES CPU::opcode0xE1() {

    return 8;
}// set 4, C

NUM_CYCLES CPU::opcode0xE2() {
 
    return 8;
}// set 4, D

NUM_CYCLES CPU::opcode0xE3() {
  
    return 8;
}// set 4, E

NUM_CYCLES CPU::opcode0xE4() {
 
    return 8;
}// set 4, H

NUM_CYCLES CPU::opcode0xE5() {

    return 8;
}// set 4, L

NUM_CYCLES CPU::opcode0xE6() {

    return 16;
}// set 4, (HL)

NUM_CYCLES CPU::opcode0xE7() {

    return 8;
}// set 4, A


NUM_CYCLES CPU::opcode0xE8() {

    return 8;
}// set 5, B

NUM_CYCLES CPU::opcode0xE9() {

    return 8;
}// set 5, C

NUM_CYCLES CPU::opcode0xEA() {

    return 8;
}// set 5, D

NUM_CYCLES CPU::opcode0xEB() {

    return 8;
}// set 5, E

NUM_CYCLES CPU::opcode0xEC() {

    return 8;
}// set 5, H

NUM_CYCLES CPU::opcode0xED() {

    return 8;
}// set 5, L

NUM_CYCLES CPU::opcode0xEE() {

    return 16;
}// set 5, (HL)

NUM_CYCLES CPU::opcode0xEF() {

    return 8;
}// set 5, A


NUM_CYCLES CPU::opcode0xF0() {
    
    return 8;             
}// set 6, B

NUM_CYCLES CPU::opcode0xF1() {
  
    return 8;
}// set 6, C

NUM_CYCLES CPU::opcode0xF2() {

    return 8;
}// set 6, D

NUM_CYCLES CPU::opcode0xF3() {

    return 8;
}// set 6, E

NUM_CYCLES CPU::opcode0xF4() {
   
    return 8;
}// set 6, H

NUM_CYCLES CPU::opcode0xF5() {

    return 8;
}// set 6, L

NUM_CYCLES CPU::opcode0xF6() {
  
    return 16;
}// set 6, (HL)

NUM_CYCLES CPU::opcode0xF7() {
   
    return 8;
}// set 6, A


NUM_CYCLES CPU::opcode0xF8() {

    return 8;
}// set 7, B

NUM_CYCLES CPU::opcode0xF9() {
    
    return 8;
}// set 7, C

NUM_CYCLES CPU::opcode0xFA() {
   
    return 8;
}// set 7, D

NUM_CYCLES CPU::opcode0xFB() {
   
    return 8;
}// set 7, E

NUM_CYCLES CPU::opcode0xFC() {
    return 8;
}// set 7, H

NUM_CYCLES CPU::opcode0xFD() {
    return 8;
}// set 7, L

NUM_CYCLES CPU::opcode0xFE() {
    return 16;
}// set 7, (HL)

NUM_CYCLES CPU::opcode0xFF() {
    return 8;
}// set 7, A