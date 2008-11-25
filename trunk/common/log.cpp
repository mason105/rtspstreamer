#include "log.hpp"

namespace common { 
namespace log {
    
static log_base * app_log = NULL;

void init_logger() {
    if (app_log) {
        delete app_log;
    }
    app_log = new console_log(std::cout);
}

void init_logger(std::string filename) {
    if (app_log) {
        delete app_log;
    }
    app_log = new file_log(filename);
}

void destroy_logger() {
    if (app_log) {
        delete app_log;
    }
} 

formatter debug() { 
    return formatter(*app_log, level::debug);
}

formatter info() { 
    return formatter(*app_log, level::info);
}

formatter warning() { 
    return formatter(*app_log, level::warning);
}

formatter error() { 
    return formatter(*app_log, level::error);
}

exception_formatter throw_exception() { 
    return exception_formatter(*app_log, level::exception);
}

} }
