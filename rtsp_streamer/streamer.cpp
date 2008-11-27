#include "streamer.hpp"
#include <boost/algorithm/string.hpp>

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
	endpoint_ = boost::asio::ip::tcp::endpoint(
			boost::asio::ip::address::from_string(addr[0])
			, boost::lexical_cast<unsigned short>(addr[1])
		);

	name_ = "[streamer/" + address + "]";

	connect();
}

streamer::streamer(std::string const & ip, unsigned short port)
	: socket_(io_service_)
{
	endpoint_ = boost::asio::ip::tcp::endpoint(
			boost::asio::ip::address::from_string(ip), port);		
	
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
	socket_.connect(endpoint_);
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
	unsigned int len = socket_.read_some(boost::asio::buffer(&data[0], data.size()));
	return len;
}

}
