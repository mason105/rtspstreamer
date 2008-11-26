#include "main.hpp"
#include "streamer.hpp"

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/assign/list_of.hpp>

namespace stream_server {

service::service()
	: common::service(((common::signal_builder()),(SIGINT)))
	, name_("[stream_server]")
{}

void service::start()
{
	logger::info() << name() << " Init the server";
	
}

int service::run(int argc, char ** argv)
{
	streamer_.reset(new streamer(argv[1]));
	logger::info() << name() << " Server started";

	std::vector<char> read_buf(10000, 0);
	while (running()) {
		std::cout << "Text to send: ";
		std::string buf, line;
		while (true) {
			std::cin >> line;
			if (line == "EOF") break;
			buf += line + "\r\n";
		}
		logger::debug() << "Sending:\n" << buf;
		streamer_->send(buf);

		int len = streamer_->read(read_buf);
		std::string tmp(&buf[0], len);
		logger::debug() << "Recieved:\n" << tmp;
		boost::this_thread::yield();
	}
	logger::info() << name() << " Server stopped";
	return 0;
}

void service::on_terminate_signal()
{
	common::service::on_terminate_signal();
}

} // namespace stream_server

int main(int argc, char ** argv)
{
	common::logger::init_logger();
	stream_server::service s;
	return s(argc, argv);
}
