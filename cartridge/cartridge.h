#pragma once

#include <vector>
#include <string>

class Cartridge {
private:
    std::string title;
    std::uint8_t type;
    std::uint8_t romSize;
    std::uint8_t ramSize;
    void parseAndCheckHeader();

public:
    Cartridge(std::string romFile);
    std::vector<uint8_t> rom;
};