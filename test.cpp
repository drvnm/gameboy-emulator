#include <iostream>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    std::cout << "Gameboy Emulator" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}