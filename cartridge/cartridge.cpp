#include "cartridge.h"

#include <stdexcept> 
#include <iostream>
#include <fstream>

Cartridge::Cartridge(std::string romFile) {
    std::cout << "Loading rom..." << std::endl;
    
    std::vector<uint8_t> rom;
    std::ifstream file(romFile, std::ios::binary);
    
    while (!file.eof())
    {
        uint8_t byte;
        file.read(reinterpret_cast<char *>(&byte), sizeof(byte));
        rom.push_back(byte);
    }

    this->rom = rom;
    parseAndCheckHeader();

    std::cout << "Title: " << title << std::endl;
    std::cout << "Type: " << (int)type << std::endl;
    std::cout << "ROM Size: " << (int)romSize << std::endl;
    std::cout << "RAM Size: " << (int)ramSize << std::endl;
}

void Cartridge::parseAndCheckHeader() {
    std::cout << "Parsing cartridge header..." << std::endl;
    // if (rom[0x104] != 0xCE) {
    //     throw std::runtime_error("Invalid ROM: Nintendo logo not found");
    // }
    this->title = std::string(rom.begin() + 0x134, rom.begin() + 0x143);
    this->type = rom[0x147];
    this->romSize = rom[0x148];
    this->ramSize = rom[0x149];
}