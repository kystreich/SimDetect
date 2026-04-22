#include <bit>
#include <charconv>
#include <cassert>
#include <cstring>
#include <span>
#include "disassembler.h"
#include "opcode.h"
#include "../logger/logger.h"

namespace SimDetect::Evm {
    // TODO: move this to cbor namespace
    bool isCbor(Byte input) {
        // mask out bits defining kv count, only checks for maps but if it's not a map we don't really care.
        return (input & 0xE0) == 0xA0;
    }

    bool isAligned(size_t size) {
        /*  first condition is a 0 check, second is a bitwise operation,
            powers of two only have one bit set, so when we -1 it forces every lower bit to flip.
            then we can AND it against the original.
            https://stackoverflow.com/a/33083952
        */
        return size && !(size & (size - 1));
    }
    
    std::string removeHeader(std::string_view input) {
        if (input.starts_with("0x")) {
            return std::string(input.substr(2));
        }

        return std::string(input);
    }

    std::optional<Byte> byteFromChars(std::string_view input) {
        std::uint8_t byteVal;
        
        auto result = std::from_chars(input.data(), input.data() + input.size(), byteVal, 16);
        if (result.ec != std::errc{}) {
            Logger::err() << "Error reading byte";
            return std::nullopt;
        }

        return byteVal;
    }

    std::optional<std::vector<Byte>> stringToByteArray(std::string_view input) {
        std::uint64_t stringCursor{0};

        std::vector<Byte> returnVal;
        returnVal.reserve(input.size() / 2);

        while (stringCursor < input.size()) {
            auto result = byteFromChars(input.substr(stringCursor, 2));
            if (!result.has_value()) return std::nullopt;

            returnVal.push_back(result.value());
            stringCursor += 2;
        }

        return returnVal;
    }

    // Uses memcpy so reads are O(1)    
    template <typename T>
    T Disassembler::immediateRead() {
        if ((cursor_ + sizeof(T)) > contractBytecode_.size())
            throw std::out_of_range("Attempted read beyond bytecode");

        T value;
        std::memcpy(&value, contractBytecode_.data() + cursor_, sizeof(T));

        cursor_ += sizeof(T);
        // EVM is big endian
        return std::byteswap(value);
    }

    const std::span<const Byte> Disassembler::readBlob(size_t count) {
        if ((cursor_ + count) > contractBytecode_.size())
            throw std::out_of_range("Attempted read beyond bytecode");

        if (count > 32) // each evm item is 256 bit
            throw std::out_of_range("Attempted read exceeds max size");        

        std::span<const Byte> byteSpan{contractBytecode_.begin() + cursor_, count};

        cursor_ += count;
        return byteSpan;
    }

    Disassembler::Disassembler(std::string_view inputBuffer)
        :cursor_{0} 
        ,contract_{}
        {
            auto cleanInput = removeHeader(inputBuffer);
            contractBytecode_.reserve(cleanInput.size() / 2); 
            
            auto byteArray = stringToByteArray(removeHeader(inputBuffer));
            
            if (!byteArray.has_value())
                throw std::logic_error("Invalid hex conversion in input buffer");

            contractBytecode_ = byteArray.value();
        }

    Contract Disassembler::disassemble() {
        while (cursor_ < contractBytecode_.size()) {
            Byte byte = immediateRead<Byte>();
            auto resolved = resolveInstruction(byte);
            
            ContextualizedInstruction instruction{resolved};
            instruction.offset = cursor_ - 1; // cursor is incremented on the read so itll always be 1 ahead

            if (resolved.paramLookahead > 0) {
                auto blob = readBlob(resolved.paramLookahead);
                instruction.param = blob;
            }

            contract_.instructionSet.push_back(instruction);
        }

        return contract_;
    }
}