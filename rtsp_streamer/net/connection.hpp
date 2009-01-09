#ifndef __net_connection_hpp__
#define __net_connection_hpp__

#include "address.hpp"

namespace net {
    
    /** Base connection class */
    class connection {
    public:
        struct callback {
            virtual void on_connected() = 0;
            virtual void on_disconnected() = 0;
            virtual void on_data(packet::pointer p) = 0;
        };
        
    public:
        // pointer type
        typedef boost::shared_ptr<connection> pointer;
        
        // virtual destructor
        virtual ~connection() {}
        
        // connect
        virtual void connect() = 0;
        // send packet
        virtual void send(packet::pointer p) = 0;
        // Close connection
        virtual void close() = 0;
        
        // TBD: Set socket parameters
        
        // Call repeatedly for the callback states
        virtual void timeslice(callback & cb) = 0;
        
        // Print connection name
        virtual std::string & name() throw() const = 0;
    };

    class tcp_connection : public connection {
    public:
        // pointer type
        typedef boost::shared_ptr<tcp_connection> pointer;
        
        // set TCP_NO_DELAY flag
        virtual void set_tcp_nodelay(bool enabled) = 0;
    };
    
} // namespace net

#endif // __net_connection_hpp__