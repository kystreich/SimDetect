#include "format"
#include "fstream"
#include "../lib/logger/logger.h"
#include "../lib/evm/disassembler.h"

int main() {
    std::ifstream file("bytecode.txt");

    if (!file.is_open()) {
        SimDetect::Logger::err() << "Failed to open file";
        return 1;
    }

    std::string line;
    std::getline(file, line);

    auto disa = SimDetect::Evm::Disassembler{line};
    auto x = disa.disassemble();
  
    // for (const auto& instruction : x.instructionSet) {
    //     SimDetect::Logger::info() << std::format("{:x} | {:#04x} | {} > {}", instruction.offset, instruction.opcode, instruction.name, instruction.paramLookahead);
    // }
    SimDetect::Logger::info() << std::format("Disassembled {} instructions", x.instructionSet.size());
}