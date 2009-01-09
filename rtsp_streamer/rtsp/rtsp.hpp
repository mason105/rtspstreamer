#ifndef __rtsp_streamer_rtsp_hpp__
#define __rtsp_streamer_rtsp_hpp__

#include "common/base.hpp"
#include "common/logger.hpp"
#include "common/singleton.hpp"

namespace rtsp {

namespace logger = common::logger;

typedef unsigned int SessionId;

class config : public common::singleton<config> {
protected:
    friend class common::singleton<config>;
    config()
        : user_agent("RTSP streamer v1.0")
    {}
public:
    std::string user_agent;
};

class session
    : public common::base 
    , private boost::noncopyable {
public:
    typedef boost::shared_ptr<session> pointer;

    /** Get session id */
    virtual SessionId const id() const = 0;
    /** Get stream packet */
    virtual packet::pointer get_packet() = 0;
};

class factory : public common::base {
public:
    /** Factory instance */
    static factory & instance();

    /** Create the session */
    virtual session::pointer create_session(std::string const & username
            , std::string const & password
            , std::string const & address) = 0;
    /** Get the session */
    virtual session::pointer const get_session(SessionId sid) const = 0;
    /** Remove the session */
    virtual void remove_session(SessionId sid) = 0;
};

} // namespace rtsp

#endif // __rtsp_streamer_rtsp_hpp__
