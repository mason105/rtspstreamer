#ifndef __rtsp_streamer_config_hpp__
#define __rtsp_streamer_config_hpp__

#include "common.hpp"

namespace rtsp_streamer {

class config : public common::singleton<config> {
public:
    struct {
        std::string user_agent;
    } rtsp;
};

} // namespace rtsp_streamer

#endif // __rtsp_streamer_config_hpp__
