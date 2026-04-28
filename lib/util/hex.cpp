#include <string>
#include <span>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <iomanip>

namespace SimDetect::Utils {
    std::string convert(std::span<const std::uint8_t> data) {
        std::ostringstream ss;
        ss << std::hex << std::setfill('0');
        for (auto b : data) {
            ss << std::setw(2) << static_cast<unsigned>(b);
        }
        return ss.str();
    }
}