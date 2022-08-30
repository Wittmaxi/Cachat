#include <iostream> 

void printHello () {
    std::cout << "Hello World \n";
}

constexpr void (*intrinsics[24])(void) = {
    printHello
};