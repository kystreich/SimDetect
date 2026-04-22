#pragma once

#include <cstdint>
#include <span>

namespace SimDetect::Evm {
    using Byte = std::uint8_t;

    struct Instruction {
        const char* name; // using constexpr so this has to be a literal
        Byte opcode;
        Byte stackInput;
        Byte stackOutput;
        Byte paramLookahead;
    };
    
    struct ContextualizedInstruction : Instruction {
        std::span<const Byte> param;
        std::uint16_t offset; // as of now instructions are capped to 24kb (eip-170), however there are outstanding proposals to increase this (EIP-7907) so this may need to change.
    };

    const Instruction& resolveInstruction(std::uint8_t opcode);
}