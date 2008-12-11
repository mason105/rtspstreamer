#ifndef __rtsp_streamer_commands_hpp__
#define __rtsp_streamer_commands_hpp__

#include "rtsp.hpp"
#include <sstream>

namespace rtsp {

class cseq {
public:
    cseq() : seq_(1) {}
    operator unsigned int() { return seq_++; }
private:
    volatile unsigned int seq_;
};

class target {
public:    
    typedef boost::shared_ptr<target> pointer;
    target(std::string const & username
            , std::string const & password
            , std::string const & address)
        : username_(username)
        , password_(password)
        , address_(address)
    {}
    inline std::string const & username() const {
        return username_;
    }
    inline std::string const & password() const {
        return password_;
    }
    inline std::string const & address() const {
        return address_;
    }
private:
    std::string username_;
    std::string password_;
    std::string address_;
};

class generic_command : public command {
public:
    generic_command(cseq & csq, target::pointer trg)
        : cseq_(csq)
        , target_(trg)
    {}

protected:
    void header(std::string const & command_name, std::ostringstream & oss);
    void footer(std::ostringstream & oss);

protected:
    cseq & cseq_;
    target::pointer target_;
};

class options_command : public generic_command {
public:
    options_command(cseq & csq, target::pointer trg)
        : generic_command(csq, trg)
        , name_("[options_command]")
    {}
    
    virtual std::string operator()();
    virtual std::string const & name() const {
        return name_;
    }
private:
    std::string name_;
};

} // namespace rtsp

#endif // __rtsp_streamer_rtsp_hpp__
