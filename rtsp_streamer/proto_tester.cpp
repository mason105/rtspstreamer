#include "proto_tester.hpp"
#include "streamer.hpp"

namespace rtsp_streamer {

proto_tester::proto_tester(std::string const & filename, streamer & strm)
    : filename_(filename)
    , streamer_(strm)
    , name_("[proto_tester]")
{}
    
void proto_tester::start()
{
    logger::debug() << name() << " Starting thread";
    thread_.reset(new boost::thread(boost::bind(&proto_tester::run, this)));
    running_ = true;
}

void proto_tester::stop()
{
    if (running_) {
        logger::debug() << name() << " Stopping thread";
        running_ = false;
        thread_->join();
    }
}

void proto_tester::run()
{
    std::ifstream f(filename_.c_str(), std::ios::in);
    if (!f) {
        logger::error() << name() << " Couldn't open proto file '" << filename_ << "'";
        running_ = false;
        return;
    }

    logger::debug() << name() << " Thread started";

    std::vector<char> recv_buf;
    while (running_) {
        try {
            std::string buf = get_send_buf(f); 
            if (!buf.empty()) {
                streamer_.send(buf);
                logger::debug() << "Data:\n" << buf;
            }
            streamer_.read(recv_buf);
            logger::debug() << name() << " Read " << recv_buf.size() << " bytes";
            if (!recv_buf.empty()) {
                logger::debug() << std::string(&recv_buf[0], recv_buf.size());
            }
            sleep(1);
        } catch (std::exception & e) {
            logger::error() << name() << " Exception: " << e.what();
            running_ = false;
        }
    }

    logger::debug() << name() << " Thread stopped";

}

std::string proto_tester::get_send_buf(std::ifstream & f)
{
    static std::string crlf = "\r\n";
    std::string ret;
    char buf[10001];
    while (!f.eof()) {
        f.getline(&buf[0], 10000);
        if (boost::starts_with(buf, "EOF")) {
            return ret;
        }
        size_t sz = strlen(buf);
        if (sz == 0) {
            continue;
        }
        if (buf[sz - 1] == '\r') {
            buf[strlen(buf) - 1] = 0;
        }
        ret += buf + crlf;
    }
    return ret;
}

} // namespace rtsp_streamer
