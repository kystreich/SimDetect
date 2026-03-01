/* Simplified version of tokyospliff's logger from Hell2025
   https://github.com/livinamuk/Hell2025/blob/main/Hell2025/Hell2025/src/Common/HellLogging.cpp
*/
#include "iostream"
#include "logger.h"

namespace SimDetect::Logger {
    std::string ansiEscape() { return "\e[0m"; }
    
    std::string levelAnsi(Level level) {
        switch(level) {
            case (Level::ERR):      return "\e[0;101;30m";
            case (Level::FATAL):    return "\e[0;105;30m";
            case (Level::INFO):     return "\e[0;106;30m";
            case (Level::OK):       return "\e[0;102;30m";
            case (Level::WARN):     return "\e[0;103;30m";
            default:                return "\e[0;103;47m"; 
        }
    }

    std::string levelName(Level level) {
        switch(level) {
            case (Level::ERR):      return "ERR  ";
            case (Level::FATAL):    return "FATAL";
            case (Level::INFO):     return "INFO ";
            case (Level::OK):       return "OK   ";
            case (Level::WARN):     return "WARN ";
            default:                return "FACK ";
        }
    }

    Log::Log(Level level) {
        messageString_ << levelAnsi(level) << "[ "  << levelName(level)  << " ]" << ansiEscape() << " ";
    }
    
    Log& Log::operator<<(std::string_view input) {
        messageString_ << input;
        return *this;
    }

    Log::~Log() {
        std::cout << messageString_.str() << "\e[0m\n";
    }
}