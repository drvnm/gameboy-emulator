g++ main.cpp  `
memory/memory.cpp `
cartridge/cartridge.cpp `
common/defs.cpp `
cpu/cpu.cpp `
cpu/registers.cpp `
cpu/cpu_instructions/alu.cpp `
cpu/cpu_instructions/branching.cpp `
cpu/cpu_instructions/control.cpp `
cpu/cpu_instructions/load.cpp `
cpu/cpu_instructions/singlebit.cpp `
cpu/cpu_instructions/rotate.cpp `
display/display.cpp `
emulator/emulator.cpp `
-I"../SDL2/i686-w64-mingw32/include" `
-L"../SDL2/i686-w64-mingw32/lib" -Wall -lmingw32 `
-lSDL2main -lSDL2  ; ./a.exe '..\sm83\v1\c6.json'
