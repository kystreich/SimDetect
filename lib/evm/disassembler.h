#pragma once

#include <span>
#include <string_view>
#include <vector>
#include <optional>
#include "opcode.h"

namespace SimDetect::Evm {
    struct Contract {
        std::vector<ContextualizedInstruction> instructionSet;
        std::optional<std::vector<Byte>> metadataHash; // Some contracts have a hash which can be verified and resolved to IPFS/Swarm for metadata
    };
    
    class Disassembler {
        private:
            std::vector<Byte> contractBytecode_;
            std::uint64_t cursor_;
            Contract contract_;
            
            template <typename T>
            T immediateRead();
            const std::span<const Byte> readBlob(size_t count);
            std::optional<std::vector<Byte>> readMeta();
            
        public:
            explicit Disassembler(std::string_view inputBuffer);
            
            Contract disassemble();
    };
}