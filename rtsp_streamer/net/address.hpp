#ifndef __net_address_hpp__
#define __net_address_hpp__

#include <string>
#include <boost/lexical_cast.hpp>

#include "common/exception.hpp"

namespace net {
    namespace sp = boost::spirit;

    struct wrong_address : common::exception {
        wrong_address(std::string const & addr)
            : common::exception("Wrong formatted address: " + addr)
        {}
    };
    
    struct address {
        // ip:port or hostname:port
        address(std::string const & host) {
            std::string::pos p = host.find(":");
            if (p == std::string::npos) {
                throw wrong_address(host);
            }
            try {
                ip_ = host.substr(0, p);
                port_ = boost::lexical_cast<short>(host.substr(p + 1));
            } catch (std::exception & e) {
                throw wrong_address(host);
            }
        }
        // ip - ip or hostname to be resolved
        address(std::string const & ip, short port)
            : ip_(hostname)
            , port_(port)
        {}
        address(const address & addr)
            : ip_(addr.ip_)
            , port_(addr.port_)
        {}
        std::string const & ip() const {
            return ip_;
        }
        short const port() const {
            return port_;
        }
        std::string to_string() const {
            return ip_ + ":" + boost::lexical_cast<std::string>(port_);
        }
        
    private:
        std::string ip_;
        short port_;
    };

} // namespace net

#endif // __net_address_hpp__
