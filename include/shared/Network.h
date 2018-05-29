//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORK_H
#define CPP_INDIE_STUDIO_NETWORK_H

#include <cstdio>
#include <mutex>

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

#endif //CPP_INDIE_STUDIO_NETWORK_H
