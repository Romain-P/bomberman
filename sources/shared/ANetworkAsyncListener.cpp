//
// Created by romain on 29/05/18.
//

#include "shared/ANetworkAsyncListener.h"
#include <sys/epoll.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <iostream>

void NetworkAsyncListener::start() {
    _server_fd = defineServerFd();

    if (_server_fd <= ERROR)
        eprintf("NetworkAsyncListener::defineServerFd(): invalid server socket file descriptor\n");
    else if ((_epoll_fd = epoll_create(1)) == ERROR)
        perror("epoll_create");
    else if (!addListened(_server_fd))
        eprintf("error adding server socket fd (%d) to the epoll instance %d\n", _server_fd, _epoll_fd);
    else if (!handleSigint())
        eprintf("error trying to listen sigint");
    else {
        waitNotifications();
        return;
    }

    throw std::runtime_error("NetworkAsyncListener::start(): failed");
}

void NetworkAsyncListener::waitNotifications() {
    epoll_event_t ev;
    signalinfo_t info;

    bool interrupted = false;

    while (!isClosed()) {
        if (!epoll_wait(_epoll_fd, &ev, 1, 10))
            continue;
        int notified = ev.data.fd;

        if (notified == _signal_fd) {
            if (read(_signal_fd, &info, sizeof(info)) == sizeof(info) && info.ssi_signo == SIGINT) {
                interrupted = true;
                break;
            }
        } else
            onSocketNotified(notified);
    }

    onListenerClosed(interrupted);
}


bool NetworkAsyncListener::addListened(socket_fd_t socket) {
    epoll_t epoll = { 0 };
    epoll.events = EPOLLIN;
    epoll.data.fd = socket;

    if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, socket, &epoll) == ERROR) {
        perror("epoll_ctl");
        eprintf("[EpollInstance %d]: error adding new socket (id=%d)\n", _epoll_fd, socket);
        return false;
    }
    return true;
}

bool NetworkAsyncListener::delListened(socket_fd_t socket) {
    epoll_t epoll = { 0 };
    epoll.events = EPOLLIN;
    epoll.data.fd = socket;

    if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, socket, &epoll) == ERROR) {
        perror("epoll_ctl");
        eprintf("[EpollInstance %d]: error removing socket (id=%d)\n", _epoll_fd, socket);
        return false;
    }
    return true;
}

bool NetworkAsyncListener::handleSigint() {
    sigset_t all, sw;

    sigfillset(&all);
    sigprocmask(SIG_SETMASK, &all, nullptr);
    sigemptyset(&sw);
    sigaddset(&sw, SIGINT);

    if ((_signal_fd = signalfd(-1, &sw, 0)) == ERROR)
        perror("signalfd");
    else if (!addListened(_signal_fd))
        eprintf("cant add signalfd to the epoll instance");
    else
        return true;
    return false;
}

NetworkAsyncListener::~NetworkAsyncListener() {
    if (_signal_fd != ERROR)
        ::close(_signal_fd);

    if (_epoll_fd != ERROR)
        ::close(_epoll_fd);
}

void NetworkAsyncListener::close() {
    lock_t lock(_locker);
    _closed = true;
}

bool NetworkAsyncListener::isClosed() {
    lock_t lock(_locker);
    return _closed;
}
