#ifndef __stream_server_main_hpp
#define __stream_server_main_hpp

#ifdef WIN32
#pragma once
#endif

#include <set>
#include <vector>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace common {

typedef std::set<int> signal_list_t;

struct signal_callback {
	virtual void on_terminate_signal() = 0;
	virtual void on_offload_signal() = 0;
	virtual void on_reload_signal() = 0;
};

class service : public signal_callback {
public:
	service(signal_list_t const & term_signals
		, signal_list_t const & reload_signals
		, signal_list_t const & offload_signals);

	// check if service is running
	inline bool running() const {
		return running_;
	}
	// check if service is offloaded
	bool offloaded() const {
		return offloaded_;
	}

public:	// can be overloaded
	virtual void on_terminate_signal();
	virtual void on_offload_signal();
	virtual void on_reload_signal();

private:
	bool running_;
	bool offloaded_;
};

} // namespace stream_server

#endif
