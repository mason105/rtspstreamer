#ifndef __net_transport_hpp__
#define __net_transport_hpp__

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include "address.hpp"

namespace net {

    /** Transport factory */
    class transport {
    public:
        static transport & instance();
        
        // Create TCP/UDP connection to the specified address (does not connect!!!)
        virtual connection::pointer create_tcp_connection(address const & addr) = 0;
        virtual connection::pointer create_udp_connection(address const & addr) = 0;
    };

} // namespace net

#endif // __net_transport_hpp__