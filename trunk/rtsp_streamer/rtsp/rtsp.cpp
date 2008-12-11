#include "rtsp.hpp"
#include "session.hpp"
#include "common/map.hpp"

namespace rtsp {

class factory_impl : public factory {
public:
    factory_impl();
    session::pointer create_session(std::string const & username
            , std::string const & password
            , std::string const & address);
    session::pointer const get_session(SessionId sid) const;
    void remove_session(SessionId sid);

    std::string const & name() const {
        return name_;
    }

private:
    std::string name_;
    volatile SessionId id_counter_;

    typedef common::map<SessionId, session::pointer> session_map_t;
    session_map_t sessions_;
};

factory & factory::instance() 
{
    static factory_impl fi;
    return fi;
}

factory_impl::factory_impl()
    : name_("[rtsp_factory]")
    , id_counter_(1)
{}

session::pointer factory_impl::create_session(std::string const & username
            , std::string const & password
            , std::string const & address)
{
    session::pointer ses(
            new generic_session(id_counter_++
                , target::pointer(new target(username, password, address)))
            );
    sessions_.insert(ses->id(), ses);
    logger::info() << name() << " Session with id = " << ses->id() << " created";
    return ses;
}

session::pointer const factory_impl::get_session(SessionId sid) const
{
    return sessions_[sid];
}

void factory_impl::remove_session(SessionId sid)
{
    sessions_.erase(sid);
    logger::info() << name() << " Session with id = " << sid << " destroyed";
}

} // namespace rtsp
