#include "service.hpp"
#include <signal.h>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace process_signal {

using namespace common;

struct instance {
	typedef boost::shared_ptr<instance> pointer;

	signal_callback & callback_;
	std::set<int> term_signals_;
	std::set<int> reload_signals_;
	std::set<int> offload_signals_;

	instance(signal_callback & callback
			, signal_list_t const & term_signals
			, signal_list_t const & reload_signals
			, signal_list_t const & offload_signals)
		: callback_(callback)
		, term_signals_(term_signals)
		, reload_signals_(reload_signals)
		, offload_signals_(offload_signals)
	{}

	void handle(int sig) {
		if (term_signals_.find(sig) != term_signals_.end()) {
			callback_.on_terminate_signal();
		} else if (reload_signals_.find(sig) != reload_signals_.end()) {
			callback_.on_reload_signal();
		} else if (offload_signals_.find(sig) != offload_signals_.end()) {
			callback_.on_offload_signal();
		} else {
		}
	}
};

class handler {
public:
	void add_instance(instance::pointer s) {
		instance_ = s;
		std::for_each(s->term_signals_.begin()
			, s->term_signals_.end()
			, boost::bind(signal, _1, &handler::handle));
		std::for_each(s->reload_signals_.begin()
			, s->reload_signals_.end()
			, boost::bind(signal, _1, &handler::handle));
		std::for_each(s->offload_signals_.begin()
			, s->offload_signals_.end()
			, boost::bind(signal, _1, &handler::handle));
	}
	static void handle(int sig);
	
private:
	instance::pointer instance_;
} signal_handler;

void handler::handle(int sig) {
	signal_handler.instance_->handle(sig);
}

}

namespace common {

service::service(signal_list_t const & term_signals
		, signal_list_t const & reload_signals
		, signal_list_t const & offload_signals)
{
	process_signal::signal_handler.add_instance(
		process_signal::instance::pointer(new process_signal::instance(*this
				, term_signals
				, reload_signals
				, offload_signals))
		);
}

void service::on_terminate_signal()
{
}

void service::on_offload_signal()
{
}

void service::on_reload_signal()
{
}

}
