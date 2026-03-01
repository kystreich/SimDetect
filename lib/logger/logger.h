#pragma once

#include <sstream>
namespace SimDetect::Logger {
    enum Level {
        OK,
        INFO,
        WARN,
        ERR,
        FATAL
    };

    class Log {
        public:
            Log(Level level);
            ~Log();

            Log& operator<<(std::string_view input);
        
        private:
            std::ostringstream messageString_;
    };

    inline Log ok()     { return Log(Level::OK); };
    inline Log info()   { return Log(Level::INFO); };
    inline Log warn()   { return Log(Level::WARN); };
    inline Log err()    { return Log(Level::ERR); };
    inline Log fatal()  { return Log(Level::FATAL); };
}