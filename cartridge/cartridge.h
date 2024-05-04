#pragma once

#include <vector>
#include <string>

class Cartridge {
private:
    std::vector<uint8_t> rom;
    std::string title;
    std::uint8_t type;
    std::uint8_t romSize;
    std::uint8_t ramSize;
    void parseAndCheckHeader();

public:
    Cartridge(std::vector<uint8_t> rom);
    

};