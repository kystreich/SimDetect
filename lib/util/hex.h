#pragma once

#include <string>
#include <span>

namespace SimDetect::Utils {

    std::string convert(std::span<const std::uint8_t> data);
}