#include "emulator.h"
#include <SDL2/SDL.h>
#include <chrono>

const int MAX_CYCLES = 70224;
const float FPS = 59.73;
const float DELAY_TIME = 1000.0f / FPS;

Emulator::Emulator(CPU *cpu, Display *display, Memory *memory, Cartridge *cartridge)
{
    this->cpu = cpu;
    this->display = display;
    this->memory = memory;
    this->cartridge = cartridge;
}

void Emulator::run()
{
    bool quit = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> current, previous;
    previous = std::chrono::high_resolution_clock::now();

    while (cpu->registers.pc < 69905)
    {
        current = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration<float, std::milli>(current - previous);
        uint8_t cycles = cpu->step();
        display->update(cycles);
        cpu->handleInterrupts();

        // if (elapsed.count() < DELAY_TIME)
        // {
        //     while (elapsed.count() < DELAY_TIME)
        //     {
        //         current = std::chrono::high_resolution_clock::now();
        //         elapsed = std::chrono::duration<float, std::milli>(current - previous);
        //     }

        //     previous = current;

        // }


        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        if (quit) {
            break;
        }
    }
}