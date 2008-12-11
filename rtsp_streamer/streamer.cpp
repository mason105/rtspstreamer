#include "streamer.hpp"

using namespace boost::asio::ip;
namespace spirit = boost::spirit;

namespace rtsp_streamer {

streamer::streamer(std::string const & address)
	: socket_(io_service_)
{
    static std::string trait(":");
    std::vector<std::string> addr;
    boost::algorithm::split(addr, address, boost::algorithm::is_any_of(trait));
    if (addr.size() != 2) {
        throw address_syntax_failure(address);
    }
    
    spirit::uint_parser<unsigned, 10, 1, 3> uint3_p;
    spirit::rule<> ip_rule = 
           uint3_p >> spirit::ch_p('.')
        >> uint3_p >> spirit::ch_p('.')
        >> uint3_p >> spirit::ch_p('.')
        >> uint3_p;
    if (!spirit::parse(addr[0].c_str(), ip_rule).full) {
	    tcp::resolver resolver_(io_service_);
    	tcp::resolver::query query_(tcp::v4(), addr[0], addr[1]);
	    tcp::resolver::iterator iter = resolver_.resolve(query_);

	    endpoint_ = *iter;
    } else {
	    endpoint_ = tcp::endpoint(
		    	address::from_string(addr[0])
			    , boost::lexical_cast<unsigned short>(addr[1])
    		);
    }

    name_ = "[streamer/" + address + "]";

	connect();
}

streamer::streamer(std::string const & ip, unsigned short port)
	: socket_(io_service_)
{
	endpoint_ = tcp::endpoint(
			address::from_string(ip), port);		
	
	name_ = "[streamer/" + ip + ":" + boost::lexical_cast<std::string>(port) + "]";

	connect();
}

streamer::~streamer()
{
	logger::debug() << name() << " Closing the socket";
	socket_.close();
}

void streamer::connect()
{
	logger::info() << name() << " Connecting to " << endpoint_;
    boost::system::error_code error;
    socket_.connect(endpoint_, error);
    if (error) {
        logger::error() << name() << " Error: " << error;
        throw common::exception("");
    }
}

void streamer::send(std::string const & data)
{
	send((void*)data.c_str(), data.length());
}

void streamer::send(std::vector<char> const & data)
{
	send((void*)&data[0], data.size());
}

void streamer::send(char const * data, unsigned int size)
{
	send((void*)data, size);
}

void streamer::send(void const * data, unsigned int size)
{
	socket_.send(boost::asio::buffer(data, size));
	logger::debug() << name() << " Sent " << size << " bytes";
}

unsigned int streamer::read(std::vector<char> & data)
{
	assert(!data.empty());
	unsigned int len = socket_.read_some(boost::asio::buffer(&data[0], data.size()));
	return len;
}

}
