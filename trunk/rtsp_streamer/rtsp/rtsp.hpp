#ifndef __rtsp_streamer_rtsp_hpp__
#define __rtsp_streamer_rtsp_hpp__

#include "common/base.hpp"
#include "common/logger.hpp"
#include "common/singleton.hpp"

namespace rtsp {

namespace logger = common::logger;

typedef unsigned int SessionId;

struct session_handshake_done : public common::exception {
    session_handshake_done(SessionId sid)
        : common::exception("Session id = "
                + boost::lexical_cast<std::string>(sid)
                + " handshake is done")
    {}
};

class config : public common::singleton<config> {
protected:
    friend class common::singleton<config>;
    config()
        : user_agent("RTSP streamer v1.0")
    {}
public:
    std::string user_agent;
};

class command : public common::base {
public:
    typedef boost::shared_ptr<command> pointer;

    virtual ~command() {}
    virtual std::string operator()() = 0;
};

class session
    : public common::base 
    , private boost::noncopyable {
public:
    typedef boost::shared_ptr<session> pointer;

    /** Get session id */
    virtual SessionId const id() const = 0;
    /** 
     * Get the next command to send
     * \throw session_handshake_done when session handshake is over
     * \return empty pointer if there's nothing to send
     */
    virtual command::pointer next() = 0;
    /**
     * Called when there's a reply to the command
     */
    virtual void on_reply(std::string const & reply) = 0;
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
