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
            Contract contract_;
            std::optional<std::string> getMetadata();
            
        public:
            explicit Disassembler(std::string_view inputBuffer) 
                : stringBuffer_(inputBuffer)
                , contract_{}
                {}

            Contract disassemble();
    };
}