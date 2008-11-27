#ifndef __rtsp_streamer_module_hpp__
#define __rtsp_streamer_module_hpp__

#include "common.hpp"

namespace rtsp_streamer {

/** Base class for every streamer module */
class module : public common::base {
public:
    virtual ~module() {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool const running() const = 0;
};

}

#endif // __rtsp_streamer_module_hpp__
