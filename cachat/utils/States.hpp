#include <cstdint>
#include <vector>

struct States {
    bool running = true;
    uint32_t exitCode = 0;
    uint32_t instructionPointer = 0; 
    uint32_t dataRegister = 0;
    std::vector <uint32_t> stack;
};