#pragma once

#include <vector>
#include "../opcode.h"

namespace SimDetect::Cfg {
    using Offset = std::uint16_t;

    class Block {
        friend class ControlFlowGraph;
        private:
            Offset offset_;
            std::vector<Evm::Instruction> instructions_;
            std::vector<Offset> precedingEdges_;
            std::vector<Offset> succeedingEdges_;

        public:
            explicit Block(Offset offset)
                : offset_(offset)
                {}

            Offset getOffset() const;
            const std::vector<Evm::Instruction>& getInstructions() const;
            const Evm::Instruction& getEntry() const;
            const Evm::Instruction& getExit() const;
    };
}