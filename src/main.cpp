#include "../lib/logger/logger.h"

int main() {
    SimDetect::Logger::ok()     << "OK";
    SimDetect::Logger::info()   << "INFO";
    SimDetect::Logger::warn()   << "WARN";
    SimDetect::Logger::err()    << "ERR";
    SimDetect::Logger::fatal()  << "FATAL";
}