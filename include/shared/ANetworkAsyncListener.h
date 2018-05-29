//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKASYNCLISTENER_H
#define CPP_INDIE_STUDIO_NETWORKASYNCLISTENER_H


#include "NetworkSocket.h"

class NetworkAsyncListener {
public:

    explicit NetworkAsyncListener() = default;
    virtual ~NetworkAsyncListener();

    /**
     * Know if the listener is closed or not
     * @return  true if closed, false otherwise
     */
    bool isClosed();

protected:

    /**
     * Start listening on the server socket sent to the constructor.
     * Blocking function.
     */
    virtual void start();

    /**
     * Close the server, thread safe.
     */
    virtual void close();

    /**
     * This method will be fired when a socket has data awaiting to be read
     *
     * @param socket_id     id of the notified socket
     */
    virtual void onSocketNotified(socket_fd_t socket_id) = 0;

    /**
     * Method called when listener is stopped.
     *
     * @param interrupted    true if the listener closed due of catching a sigint signal
     */
    virtual void onListenerClosed(bool interrupted) = 0;

    /**
     * Define the server socket accepting clients
     */
    virtual socket_fd_t defineServerFd() = 0;

    /**
     * Add a new socket to be listened by the epoll instance
     *
     * @param socket    id of the socket to listen
     * @return          true on success, false otherwise
     */
    bool addListened(socket_fd_t socket);

    /**
     * Delete a socket from the epoll instance
     *
     * @param socket    id of the socket to remove
     * @return          true on success, false otherwise
     */
    bool delListened(socket_fd_t socket);

private:
    socket_fd_t _server_fd = -1;
    socket_fd_t _signal_fd = -1;
    socket_fd_t _epoll_fd = -1;

    std::mutex _locker;
    bool _closed = false;

    void waitNotifications();
    bool handleSigint();
};


#endif //CPP_INDIE_STUDIO_NETWORKASYNCLISTENER_H
