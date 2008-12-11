#ifndef __rtsp_streamer_common_hpp__
#define __rtsp_streamer_common_hpp__

#ifdef WIN32
#pragma once
// avoid asio and date_time conflict on WinSock.h
#define WIN32_LEAN_AND_MEAN
// warning on std::copy over char variable
#define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef _WIN32_WINNT
// define windows version for vista
#define _WIN32_WINNT 0x0600
#endif

#include "common/base.hpp"
#include "common/logger.hpp"
#include "common/exception.hpp"

#include <fstream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/spirit.hpp>

namespace rtsp_streamer {

namespace logger = common::logger;

}

#endif // __rtsp_streamer_common_hpp__
