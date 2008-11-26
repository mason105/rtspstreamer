#ifndef __stream_server_main_hpp__
#define __stream_server_main_hpp__

#ifdef WIN32
#pragma once
#endif

#include "common.hpp"
#include "common/service.hpp"

namespace stream_server {

class streamer;

class service : public common::service {
public:
	service();
	
	virtual void start();
	virtual int run(int argc, char ** argv);
	virtual void on_terminate_signal();

	virtual std::string const & name() const {
		return name_;
	}

private:
	std::string name_;
	boost::shared_ptr<streamer> streamer_;
};

}

#endif // __stream_server_main_hpp__
