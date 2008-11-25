#ifndef __stream_server_common_hpp__
#define __stream_server_common_hpp__

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
#include "common/log.hpp"
#include "common/exception.hpp"

namespace stream_server {

namespace log = common::log;

}

#endif // __stream_server_common_hpp__
