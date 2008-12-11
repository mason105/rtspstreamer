#include "session.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace rtsp {

class generic_session_impl {
public:
    generic_session_impl(SessionId id, target::pointer trgt);

    command::pointer next();
    void on_reply(std::string const & reply);

    std::string const & name() const {
        return name_;
    }

private:
    command::pointer idle_state();
    command::pointer options_state();
    command::pointer wait_reply();

private:
    SessionId id_;
    cseq cseq_;
    target::pointer target_;
    std::string name_;

    boost::function<command::pointer()> state_func;
};

generic_session::generic_session(SessionId id, target::pointer trgt)
    : id_(id)
    , pimpl(new generic_session_impl(id, trgt))
{}

generic_session::~generic_session()
{
    delete pimpl;
}
    
command::pointer generic_session::next()
{
    return pimpl->next();
}

void generic_session::on_reply(std::string const & reply)
{
    pimpl->on_reply(reply);
}

std::string const & generic_session::name() const 
{
    return pimpl->name();
}

/****************
 * SESSION IMPL
 */
generic_session_impl::generic_session_impl(SessionId id, target::pointer trgt)
    : id_(id)
    , target_(trgt)
    , name_("[rtsp_session/" + boost::lexical_cast<std::string>(id) + "]")
    , state_func(boost::bind(&generic_session_impl::idle_state, this))
{}

command::pointer generic_session_impl::next()
{
    return state_func();
}

void generic_session_impl::on_reply(std::string const & reply)
{
}

command::pointer generic_session_impl::idle_state()
{
    logger::info() << name() << " Initiating the session with OPTIONS"; 
    state_func = boost::bind(&generic_session_impl::options_state, this);
    return state_func();
}

command::pointer generic_session_impl::options_state()
{
    command::pointer cmd(new options_command(cseq_, target_));
    state_func = boost::bind(&generic_session_impl::wait_reply, this);
    return cmd;
}

command::pointer generic_session_impl::wait_reply()
{
    return command::pointer();
}

} // namespace rtsp

