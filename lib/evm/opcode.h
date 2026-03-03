#pragma once

#include <cstdint>

namespace SimDetect::Evm {
    struct Instruction {
        const char* name; // using constexpr so this has to be a literal
        std::uint8_t opcode;
        std::uint8_t stackInput;
        std::uint8_t stackOutput;
        std::uint8_t paramLookahead;
    };

    const Instruction& resolveInstruction(std::uint8_t opcode);
}