#include <charconv>
#include <cassert>
#include "disassembler.h"
#include "../logger/logger.h"

namespace SimDetect::Evm {
    // TODO: define more lengths here (?)
    constexpr std::size_t AddressLength = 20;

    std::optional<std::uint8_t> byteFromChars(std::string_view input) {
        std::uint8_t returnVal;
        
        auto result = std::from_chars(input.data(), input.data() + input.size(), returnVal, 16);
        if (result.ec != std::errc{}) {
            Logger::err() << "Error reading byte";
            return std::nullopt;
        }

        return returnVal;
    }

    // TODO: move this to cbor namespace
    bool isCbor(std::string_view input) {
        auto result = byteFromChars(input);
        if (!result.has_value()) {
            return false; // TODO: should probably handle this better
        }

        // mask out bits defining kv count, only checks for maps but if it's not a map we don't really care.
        return (result.value() & 0xE0) == 0xA0;
    }

    std::string_view removeHeader(std::string_view input) {
        if (input.starts_with("0x")) {
            return input.substr(2);
        }

        return input;
    }

    std::optional<std::string> Disassembler::getMetadataString() {
        auto cborLengthHex = stringBuffer_.substr(stringBuffer_.size() - 4, 4);
       
        std::uint16_t cborLength;
        auto result = std::from_chars(cborLengthHex.data(), cborLengthHex.data() + cborLengthHex.size(), cborLength, 16);
        if (result.ec != std::errc{}) {
            Logger::err() << "Error reading contract metadata";
            return std::nullopt;
        }

        if (cborLength == 0 || cborLength > stringBuffer_.size() / 2) return std::nullopt; // 100% no metadata & prevent underflow
       
        auto cborMetadata = stringBuffer_.substr(stringBuffer_.size() - 4 - (cborLength * 2), cborLength * 2);
       
        if (!isCbor(cborMetadata.substr(0, 2))) return std::nullopt; 
        
        return std::string(cborMetadata); // string_view.data() is a pointer to the underlying string (or where we started the substr in this case), will read to end of bytecode if not explicitly constructing new string.
    }

    std::optional<std::uint8_t> Disassembler::getNextByte() {
        if(cursor_ + 2 > stringBuffer_.size()) {
            Logger::err() << "Out of range, cannot advance cursor. Suspending disassembly";
            return std::nullopt;
        }

        auto returnVal = byteFromChars(stringBuffer_.substr(cursor_, 2));

        cursor_ += 2;
        return returnVal;
    }

    std::optional<std::vector<std::uint8_t>> Disassembler::getSomeBytes(uint8_t count) { // if you're trying to get more than 255 bytes you probably shouldn't
        auto cursorSnapshot = cursor_;
        
        std::vector<std::uint8_t> bytesConsumed;
        bytesConsumed.reserve(count);

        for (auto i{0uz}; i < count; ++i) {
            auto result = getNextByte();
            if (result.has_value()) {
                bytesConsumed.push_back(result.value());
            } else {
                cursor_ = cursorSnapshot;
                Logger::err() << "Failed to read next byte"; 
                return std::nullopt;
            }
        }

        return bytesConsumed;
    }

    Disassembler::Disassembler(std::string_view inputBuffer)
        :stringBuffer_{removeHeader(inputBuffer)}
        ,cursor_{0} 
        ,contract_{}
        {}

    Contract Disassembler::disassemble() {
        
    }
}