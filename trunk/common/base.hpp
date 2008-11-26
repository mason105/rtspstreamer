#ifndef __common_base_hpp__
#define __common_base_hpp__

#include <string>

typedef unsigned int uint;

namespace common {

class base {
public:
    virtual ~base() {}
    
	virtual std::string const & name() const = 0;
};

}

#endif // __common_base_hpp__
