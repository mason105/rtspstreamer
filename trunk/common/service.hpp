#ifndef __stream_server_main_hpp
#define __stream_server_main_hpp

#include "base.hpp"
#include <set>
#include <vector>
#include <signal.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace common {

typedef std::set<int> signal_list_t;

class signal_builder {
public:
    signal_builder() {}
    signal_builder & operator ,(int sig) {
        list.insert(sig);
        return *this;
    }
    operator signal_list_t & () {
        return list;
    }
private:
    signal_list_t list;
};

struct signal_callback {
    virtual ~signal_callback() {}
    virtual void on_terminate_signal() = 0;
	virtual void on_offload_signal() = 0;
	virtual void on_reload_signal() = 0;
};

class service 
	: public base
	, public signal_callback {
public:
	service(signal_list_t const & term_signals);
	service(signal_list_t const & term_signals
		, signal_list_t const & reload_signals);
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

	virtual void start() {}
	virtual int run(int argc, char ** argv) = 0;
	virtual void stop() {}

	int operator()(int argc, char ** argv);

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
