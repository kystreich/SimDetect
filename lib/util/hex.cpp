#include <string>
#include <span>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <iomanip>

namespace SimDetect::Utils {
    std::string convert(std::span<const std::uint8_t> data) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        std::ranges::for_each(data, [&](auto x) { ss << static_cast<int>(x); });

        return ss.str();
    }
}