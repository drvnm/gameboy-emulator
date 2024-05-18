#include "emulator.h"
#include <SDL2/SDL.h>
#include <chrono>

const int MAX_CYCLES = 70224;
const float FPS = 59.73;
const float DELAY_TIME = 1000.0f / FPS;

Emulator::Emulator(CPU *cpu, Display *display, Memory *memory, Cartridge *cartridge, Debugger *debugger)
{
    this->cpu = cpu;
    this->display = display;
    this->memory = memory;
    this->cartridge = cartridge;
    this->debugger = debugger;
}

void Emulator::run()
{
    bool quit = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> current, previous;
    previous = std::chrono::high_resolution_clock::now();

    while (cpu->registers.pc < 69905)
    {
        if (!debugger->doPause)
        {
            current = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration<float, std::milli>(current - previous);
            if (!cpu->halted)
            {
                uint8_t cycles = cpu->step();
                display->update(cycles);
                cpu->updateTimers(cycles);
            } else {
                std::cout << "HALTED" << std::endl;
            }
            cpu->handleInterrupts();
        }

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
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // if 1 is pressed, turn debug.pause on
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_1)
                {
                    // debugger->doPause = !debugger->doPause;
                    
                }
                // from 1 to 9, set the cpu->keyPressed to the key pressed
                if (e.key.keysym.sym >= SDLK_1 && e.key.keysym.sym <= SDLK_9)
                {
                    cpu->keyPressed(std::stoi(SDL_GetKeyName(e.key.keysym.sym)));
                }
            }
            if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_2)
                {
                    // debugger->doPrint = !debugger->doPrint;
                }
                // from 1 to 9, set the cpu->keyPressed to the key pressed
                if (e.key.keysym.sym >= SDLK_1 && e.key.keysym.sym <= SDLK_9)
                {
                    cpu->keyReleased(std::stoi(SDL_GetKeyName(e.key.keysym.sym)));
                }
            }
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_3)
                {
                    debugger->doTileRender = true;
                     
                }
            }
        }
        if (quit)
        {
            break;
        }
    }
    std::cout << "PC: " << cpu->registers.pc << std::endl;
}