#ifndef __common_logger_hpp__
#define __common_logger_hpp__

#include "exception.hpp"

#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

namespace common { 
namespace logger {
    
struct level {
    enum type {
        debug,
        info,
        warning,
        error,
        exception
    };
};

inline std::ostream &
operator<< (std::ostream & os, level::type & t) {
    switch (t) {
    case level::debug:      os << "DEBUG      ";    break;
    case level::info:       os << "INFO       ";    break;
    case level::warning:    os << "WARNING    ";    break;
    case level::error:      os << "ERROR      ";    break;
    case level::exception:  os << "EXCEPTION  ";    break;
    };
    return os; 
}

class logger_base {
public:
    virtual ~logger_base() {}
    virtual void print(std::ostringstream & s) = 0;
};

class console_logger : public logger_base {
public:
    console_logger(std::ostream & os) 
        : os(os) 
    {}

    virtual ~console_logger() {
        try {
            os.flush();
        } catch (...) {
        } 
    }
    virtual void print(std::ostringstream & s) {
        os.write(s.str().c_str(), s.str().length());
        os.flush();
    }
    
protected:
    std::ostream & os;
};


class file_logger : public logger_base {
public:
    file_logger(std::string & filename) 
    {
        f.open(filename.c_str(), std::ios::out | std::ios::app);
    }
    virtual ~file_logger() {
        try {
            if (f.is_open()) {
                f.close();
            }
        } catch (...) {
        } 
    }
    inline void print(std::ostringstream & s) {
        f.write(s.str().c_str(), s.str().length());
        f.flush();
    }
        
protected:
    std::fstream f;
};

class formatter {
public:
    formatter(logger_base & l, level::type t) 
        : l(l)
        , t(t) 
    {
        str << cur_time() << " " << t;
    }
    formatter(const formatter & f) 
        : l(f.l)
        , t(f.t) 
    {
        str << f.str.str();
    }
	virtual ~formatter() {
        try {
            str << std::endl;
            l.print(static_cast<std::ostringstream &>(str));
        } catch (...) {
        }
    }

	template <typename T> 
	std::ostream & operator<< (const T &t) {
		static_cast<std::ostream &>(str) << t;
        return str;
	}

private:
    inline std::string cur_time() {
		return boost::posix_time::to_simple_string(
			boost::posix_time::microsec_clock::universal_time()
			);
    }
        
protected:
    logger_base & l;
    level::type t;
    std::ostringstream str;
};

class exception_formatter : public formatter {
public:
    exception_formatter(logger_base & l, level::type t) 
        : formatter(l, t)
    {}
    exception_formatter(const exception_formatter & f) 
        : formatter(static_cast<formatter>(f))
    {}
    virtual ~exception_formatter() {
        throw common::exception(str.str());
    }
};

void init_logger();
void init_logger(std::string filename);
void destroy_logger();

formatter debug();
formatter info();
formatter warning();
formatter error();
exception_formatter throw_exception();

} }

#endif // __common_logger_hpp__
