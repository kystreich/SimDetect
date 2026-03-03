#include <vector>
#include <cassert>
#include "block.h"

namespace SimDetect::Cfg {
    const Evm::Instruction& Block::getEntry() const {
        assert(!instructions_.empty());
        return instructions_.front();
    }

    const Evm::Instruction& Block::getExit() const {
        assert(!instructions_.empty());
        return instructions_.back();
    }
}