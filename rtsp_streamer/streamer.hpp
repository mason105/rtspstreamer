#ifndef __stream_server_streamer_hpp__
#define __stream_server_streamer_hpp__

#ifdef WIN32
#pragma once
#endif

#include "common.hpp"

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

namespace stream_server {

struct address_syntax_failure : common::exception {
	address_syntax_failure(std::string const & address)
		: common::exception("Address syntax is wrong: " + address)
	{}
	address_syntax_failure(std::string const & address
			, unsigned int port)
		: common::exception("Address syntax is wrong: " 
			+ address
			+ ":" + boost::lexical_cast<std::string>(port))
	{}
};

class streamer : public common::base {
public:
	typedef boost::shared_ptr<streamer> pointer;

	streamer(std::string const & address);
	streamer(std::string const & ip, unsigned short port);
	~streamer();

	void send(std::string const & data);
	void send(std::vector<char> const & data);
	void send(char const * data, unsigned int size);
	void send(void const * data, unsigned int size);

	unsigned int read(std::vector<char> & data);

	virtual std::string const & name() const {
		return name_;
	}

private:
	void connect();

private:
	std::string name_;
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::endpoint endpoint_;
};

}

#endif // __stream_server_streamer_hpp__
