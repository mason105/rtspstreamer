#include "transport.hpp"
#include "asio/transport.hpp"

using namespace net;

transport & transport::instance()
{
    // TODO: Add different underlying socket I/O here (asio, socket impl, etc.)
    static transport_asio trans;
    return trans;
}