#include "display.h"
#include <SDL2/SDL.h>

#include "cpu/cpu.h"

int main(int argc, char *argv[])
{
    CPU cpu(std::vector<uint8_t>{0x87, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0xC6});
    cpu.execute();
    return 0;
    // Display display;
    // SDL_Event event;
    // bool running = true;
    // while (running)
    // {
    //     while (SDL_PollEvent(&event))
    //     {
    //         if (event.type == SDL_QUIT)
    //         {
    //             running = false;
    //         }
    //     }
    // }
    // return 0;
}