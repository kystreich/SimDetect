#include <charconv>
#include <cassert>
#include <format>
#include "disassembler.h"
#include "../logger/logger.h"

namespace SimDetect::Evm {
    std::optional<std::uint8_t> byteFromChars(std::string_view input) {
        std::uint8_t returnVal;
        
        auto result = std::from_chars(input.data(), input.data() + input.size(), returnVal, 16);
        if (result.ec != std::errc{}) {
            Logger::err() << "Error reading byte";
            return std::nullopt;
        }

        return returnVal;
    }

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

    std::optional<std::uint8_t> Disassembler::getNextByte() {
        if(cursor_ + 2 > stringBuffer_.size()) {
            Logger::err() << "Out of range, cannot advance cursor. Suspending disassembly";
            return std::nullopt;
        }

        auto returnVal = byteFromChars(stringBuffer_.substr(cursor_, cursor_ + 2));

        cursor_ = cursor_ + 2;
        return returnVal;
    }

    std::optional<std::vector<std::uint8_t>> Disassembler::getSomeBytes(uint8_t count) { // if you're trying to get more than 255 bytes you probably shouldn't
        std::vector<std::uint8_t> bytesConsumed;
        bytesConsumed.reserve(count);

        for (auto i{0uz}; i < count; ++i) {
            auto result = getNextByte();
            if (result.has_value()) {
                bytesConsumed.push_back(result.value());
            } else {
                Logger::err() << "Failed to read next byte";
                return std::nullopt;
            }
        }

        return bytesConsumed;
    }

    Contract Disassembler::disassemble() {
        
    }
}