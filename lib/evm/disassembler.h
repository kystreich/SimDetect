#pragma once

#include <string_view>
#include <vector>
#include <optional>
#include <string>
#include "opcode.h"

namespace SimDetect::Evm {
    struct Contract {
        std::vector<Instruction> instructionSet;
        std::optional<std::string> metadataHash; // Contracts have hash which can be verified and resolved to IPFS/Swarm for metadata
    };
    
    class Disassembler {
        private:
            std::string_view stringBuffer_;
            std::uint32_t cursor_;
            Contract contract_;
            std::optional<std::string> getMetadataString();
            std::optional<std::uint8_t> getNextByte();
            std::optional<std::vector<std::uint8_t>> getSomeBytes(uint8_t count);
            
        public:
            explicit Disassembler(std::string_view inputBuffer);

            Contract disassemble();
    };
}