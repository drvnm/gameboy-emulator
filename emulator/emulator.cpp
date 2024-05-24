#include "emulator.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <windows.h>

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
    SDL_Event e;

    while (!quit)
    {

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
                if (e.key.keysym.sym == SDLK_a)
                {
                    debugger->doPrint2 = !debugger->doPrint2;
                }
            }
        }

        int updatedCycles = 0;
        while (updatedCycles < MAX_CYCLES)
        {
            if (!debugger->doPause)
            {
                if (!cpu->halted)
                {
                    uint8_t cycles = cpu->step();
                    updatedCycles += cycles;
                    cpu->updateTimers(cycles);
                    display->update(cycles);
                }
                else
                {
                    std::cout << "HALTED" << std::endl;
                }
                cpu->handleInterrupts();
            }
        }
        display->renderCurrentFrame();
        current = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration<float, std::milli>(current - previous);
        previous = current;

        if (elapsed.count() < DELAY_TIME)
        {
            Sleep(30);
        }

    }

}