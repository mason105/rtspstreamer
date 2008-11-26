#include "logger.hpp"

namespace common { 
namespace logger {
    
static logger_base * app_logger = NULL;

void init_logger() {
    if (app_logger) {
        delete app_logger;
    }
    app_logger = new console_logger(std::cout);
}

void init_logger(std::string filename) {
    if (app_logger) {
        delete app_logger;
    }
    app_logger = new file_logger(filename);
}

void destroy_logger() {
    if (app_logger) {
        delete app_logger;
    }
} 

formatter debug() { 
    return formatter(*app_logger, level::debug);
}

formatter info() { 
    return formatter(*app_logger, level::info);
}

formatter warning() { 
    return formatter(*app_logger, level::warning);
}

formatter error() { 
    return formatter(*app_logger, level::error);
}

exception_formatter throw_exception() { 
    return exception_formatter(*app_logger, level::exception);
}

} }
