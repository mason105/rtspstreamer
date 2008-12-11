#include "commands.hpp"

namespace rtsp {

void generic_command::header(std::string const & command_name, std::ostringstream & oss)
{
    oss << command_name << " rtsp://"
        << target_->username() << ":"
        << target_->password() << "@"
        << target_->address() << " "
        << "RTSP 1.0\r\n";
}

void generic_command::footer(std::ostringstream & oss)
{
    oss << "CSeq: " << cseq() << "\r\n"
        << "User-Agent: " << config::instance().user_agent << "\r\n\r\n";
}

std::string options_command::operator()()
{
    std::ostringstream oss;
    generic_command::header("OPTIONS", oss);
    generic_command::footer(oss);
    return oss.str();
}

} // namespace rtsp
