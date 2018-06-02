//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORK_H
#define CPP_INDIE_STUDIO_NETWORK_H

#include <cstdio>
#include <mutex>
#include <iostream>
#include <cstdarg>

#define eprintf(format, ...)    (fprintf(stderr, (format), ##__VA_ARGS__))

#define ERROR           (-1)
#define RANDOM_PORT     (0)

using socket_fd_t = int;
using insocket_t = struct sockaddr_in;
using socket_t = struct sockaddr;
using epoll_t = struct epoll_event;
using epoll_event_t = struct epoll_event;
using signalinfo_t = struct signalfd_siginfo;
using lock_t = std::lock_guard<std::mutex>;

inline static void log(std::string const &format, ...) {
    static std::mutex locker;

    lock_t lock(locker);

    va_list list;
    va_start(list, format);
    vfprintf(stderr, format.c_str(), list);
    va_end(list);
}

#endif //CPP_INDIE_STUDIO_NETWORK_H
