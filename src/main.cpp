#include <format>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "../lib/logger/logger.h"
#include "../lib/evm/disassembler.h"
#include "../lib/util/hex.h"

int main() {
    std::ifstream file("./bytecode.txt", std::ios::binary);

    if (!file.is_open()) {
        SimDetect::Logger::err() << "Failed to open file";
        return 1;
    }

    std::string line{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    auto disa = SimDetect::Evm::Disassembler{line};
    
    auto x = disa.disassemble();
  
    std::string output{""};

    for (const auto& instruction : x.instructionSet) {
        auto paramString = SimDetect::Utils::convert(instruction.param);
        output.append(std::format("{:x} | {:#04x} | {} > {}\n", instruction.offset, instruction.opcode, instruction.name, paramString));
    }
    SimDetect::Logger::info() << output;
    SimDetect::Logger::info() << std::format("Disassembled {} instructions", x.instructionSet.size());
    
    if (x.metadataHash.has_value()) {
        SimDetect::Logger::info() << std::format("CBOR: {}", SimDetect::Utils::convert(x.metadataHash.value()));
    }
}