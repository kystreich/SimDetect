#include <charconv>
#include <format>
#include "disassembler.h"
#include "../logger/logger.h"

namespace SimDetect::Evm {
    std::optional<std::string> Disassembler::getMetadata() {
        auto cborLengthHex = stringBuffer_.substr(stringBuffer_.size() - 4, 4);
       
        std::uint16_t cborLength;
        auto result = std::from_chars(cborLengthHex.data(), cborLengthHex.data() + cborLengthHex.size(), cborLength, 16);        
        if (result.ec != std::errc{}) {
            Logger::err() << "Error reading contract metadata";
            return std::nullopt;
        }
       
        auto cborMetadata = stringBuffer_.substr(stringBuffer_.size() - 4 - (cborLength * 2), cborLength * 2);
        return std::string(cborMetadata); // string_view.data() is a pointer to the underlying string (or where we started the substr in this case), will read to end of bytecode if not explicitly constructing new string.
    }

    Contract Disassembler::disassemble() {
        
    }
}