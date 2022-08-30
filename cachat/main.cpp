#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <functional> 

#include <commander.hpp>

#include "./utils/States.hpp"
#include "../cachat_calls/calls.hpp"

uint32_t bytesToInt (std::basic_string_view<char> buffer) {
    return int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));
}

uint32_t readWord (std::basic_string_view <char> &code, States &states) {
    states.instructionPointer += 4;
    return bytesToInt (code.substr (states.instructionPointer - 4, 4));
}

uint8_t readByte (std::basic_string_view <char> &code, States &states) {
    states.instructionPointer += 1;
    return uint8_t (code.substr (states.instructionPointer - 1, 1)[0]);
}

int runLoop (std::basic_string_view<char> code) {
    States states;
    uint8_t currentOpcode;
    std::cout << "len" << code.length() << std::endl;

    while (states.running) {
        std::cout << "CODE: " << (uint) code[states.instructionPointer] << " POS: " << states.instructionPointer << "\n";
        switch ((uint8_t) code [states.instructionPointer++]) { 
            // kinda no choice, need everything to be compact 
            // to avoid weird optimizations by the compiler
            case 0x00: // exit | 1b (exit code) | calls sys_exit 
                states.running = false;
                states.exitCode = readByte (code, states);
                break;
            case 0x01: // jmp | 4b (location) | jumps
                states.instructionPointer = readWord (code, states);
                break;
            case 0x02: // mv_reg | 4b value | puts value into register
                states.dataRegister = readWord (code, states);
                break;
            case 0x03: // push | -- | put register into stack
                states.stack.push_back (states.dataRegister);
                break;
            case 0x04: // push | 4b value | puts value into register 
                states.stack.push_back (readWord (code, states));
                break;
            case 0x05: // pop | -- | pop value into register
                states.dataRegister = *(states.stack.end() - 1);
                states.stack.pop_back();
                break;
            case 0x06: // call_intrinsic | 1b function code 
                intrinsics[readByte (code, states)]();
            case 0xFF: // extended
                switch ((uint8_t) code [states.instructionPointer++]) {
                    case 0x00: // print debug
                        std::cout << "[CACHAT DEBUG] IP:" << states.instructionPointer << "; DREG: " << states.dataRegister << "\nSTACK SIZE: " << states.stack.size() << "\nSTACK: \n";
                        for (auto i : states.stack) {
                            std::cout << i << "; ";
                        }
                        std::cout << "\n";
                        break;
                }
                break;
            default:
                std::cout << "DEFAULT CASE; IP: " << states.instructionPointer << " CODE: " << (uint) code [states.instructionPointer -1] << "\n";
        }
    }
    std::cout << states.exitCode;
    return states.exitCode;
}

int main (int argc, char** argv) {
    CMD::commander commander (argc, argv);
    std::ifstream file(commander.getFlagValue<std::string>("-f"));
    std::string compileText;
    while (file) 
        file >> compileText;

    std::cout << compileText << "\n\n";

    exit(runLoop (std::basic_string_view<char> (compileText.c_str(), compileText.size())));
}