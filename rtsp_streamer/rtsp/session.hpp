#ifndef __rtsp_streamer_session_hpp__
#define __rtsp_streamer_session_hpp__
 
#include "commands.hpp"

namespace rtsp {

class generic_session_impl;

class generic_session : public session {
public:
    generic_session(SessionId id, target::pointer trg);
    ~generic_session();

    virtual command::pointer next();
    virtual void on_reply(std::string const & reply);
    virtual std::string const & name() const;

    SessionId const id() const {
        return id_;
    }

private:
    SessionId id_;
    generic_session_impl * pimpl;
};

} // namespace rtsp

#endif // __rtsp_streamer_rtsp_hpp__
