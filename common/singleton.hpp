#ifndef __common_singleton_hpp__
#define __common_singleton_hpp__

namespace common {

template <class T>
class singleton {
protected:
    singleton() {}

public:
    static T & instance() {
        static T instance_;
        return instance_;
    }
};

} // namespace common

#endif // __common_singleton_hpp__
