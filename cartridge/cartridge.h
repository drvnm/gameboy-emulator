#pragma once

#include <vector>
#include <string>

#include "../debugger/debugger.h"



class Cartridge {
private:
    Debugger* debugger;
    std::string title;
    std::uint8_t type;
    std::uint8_t romSize;
    std::uint8_t ramSize;
    void parseAndCheckHeader();

public:
    Cartridge(std::string romFile, Debugger* debugger);
    std::vector<uint8_t> rom;
};