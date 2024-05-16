// #include "display.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

#include "cartridge/cartridge.h"
#include "emulator/emulator.h"
#include "display/display.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "debugger/debugger.h"
#include "libs/json.hpp"

int main(int argc, char *argv[])
{
    // read rom from command line
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom file>" << std::endl;
        return 1;
    }

    // if it ends with .json, read the json file
    if (std::string(argv[1]).substr(std::string(argv[1]).find_last_of(".") + 1) == "json")
    {
        std ::cout << "Running JSON tests" << std::endl;
        std::fstream fJson(argv[1]);
        nlohmann::json_abi_v3_11_3::json json = nlohmann::json::parse(fJson);
        Debugger *debugger = new Debugger();
        Cartridge *cartridge = new Cartridge(argv[1], debugger);
        Memory *memory = new Memory(cartridge, debugger);
        CPU *cpu = new CPU(memory, debugger);
        // hihihihi dirty hack cause im lazy
        cpu->registers.flags.f = &cpu->registers.f;
        Display *display = new Display(memory, cpu, debugger);
        Emulator emulator(cpu, display, memory, cartridge, debugger);
        cpu->runJSONtests(json);

    }

    else
    {
        Debugger *debugger = new Debugger();
        Cartridge *cartridge = new Cartridge(argv[1], debugger);
        Memory *memory = new Memory(cartridge, debugger);
        CPU *cpu = new CPU(memory, debugger);
        // hihihihi dirty hack cause im lazy
        cpu->registers.flags.f = &cpu->registers.f;
        Display *display = new Display(memory, cpu, debugger);
        Emulator emulator(cpu, display, memory, cartridge, debugger);
        emulator.run();
    }

    // CPU cpu(rom);
    // cpu.execute();
    return 0;
}