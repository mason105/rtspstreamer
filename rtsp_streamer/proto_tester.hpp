#ifndef __rtsp_streamer_proto_tester_hpp__
#define __rtsp_streamer_proto_tester_hpp__

#include "module.hpp"

namespace rtsp_streamer {

class streamer;

class proto_tester : public module, boost::noncopyable {
public:
    proto_tester(std::string const & filename, streamer & strm);

    // from module
    void start();
    void stop();
    bool const running() const {
        return running_;
    }

    // from base
    std::string const & name() const {
        return name_;
    }

private:
    void run();
    std::string get_send_buf(std::ifstream & f);

private:
    bool running_;
    std::string filename_;
    streamer & streamer_;
    boost::shared_ptr<boost::thread> thread_;
    std::string name_;
};

}

#endif // __rtsp_streamer_proto_tester_hpp__
