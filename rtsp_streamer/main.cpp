#include "main.hpp"

#include <iostream>
#include <boost/assign/list_of.hpp>

namespace rtsp_streamer {

service::service()
	: common::service(((common::signal_builder()),(SIGINT)))
	, name_("[rtsp_streamer]")
{}

void service::start()
{
	logger::info() << name() << " Init the server";
	
}

int service::run(int argc, char ** argv)
{
//	streamer_.reset(new streamer(argv[1]));
	logger::info() << name() << " Server started";

//    proto_tester pt(argv[2], *streamer_);
//    pt.start();
	while (running()) {
		boost::this_thread::yield();
	}
	logger::info() << name() << " Server stopped";
	return 0;
}

void service::on_terminate_signal()
{
	common::service::on_terminate_signal();
}

} // namespace rtsp_streamer

int main(int argc, char ** argv)
{
	common::logger::init_logger();
	rtsp_streamer::service s;
	return s(argc, argv);
}
