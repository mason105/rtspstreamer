#ifndef __common_exception_hpp__
#define __common_exception_hpp__

#include <string>
#include <exception>

namespace common {

class exception : public std::exception {
public:
    exception(std::string msg) throw () 
        : msg(msg) 
    {}
    virtual ~exception() throw ()
    {}
    
    virtual const char * what() {
        return msg.c_str();
    }

protected:
    std::string msg;
};

}
 
#endif // __common_exception_hpp__
