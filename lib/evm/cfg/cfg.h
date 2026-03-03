#pragma once

#include <unordered_map>
#include "block.h"

namespace SimDetect::Cfg {
    class ControlFlowGraph {
        private:
            std::unordered_map<Offset, Block> blockMap;

        public:
            void addBlock(Offset offset);
            void addEdge(Offset from, Offset to);

            bool hasBlock(Offset offset) const;
            const Block& getBlock(Offset offset) const;
            const Block& getEntry() const;

            auto begin() const;
            auto end() const;
            std::size_t size();
    };
}