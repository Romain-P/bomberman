//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKSOCKET_H
#define CPP_INDIE_STUDIO_NETWORKSOCKET_H


#include <netinet/in.h>
#include <unistd.h>
#include "Network.h"

class NetworkSocket {
public:

    enum Mode { ACTIVE, PASSIVE, CHILD };

    /**
     * Create a socket:
     * Active: Connect() will be used to create the connection.
     * Passive: Bind() and Listen() will be used to create a server socket.
     *
     * @param ip        ip to connect/listen
     * @param port      port to connect
     */
    NetworkSocket(std::string const &ip, uint16_t port, Mode mode) : _ip(ip), _port(port), _mode(mode) {};
    /**
     * Create a socket from a given server file descriptor
     * Accept() will be used to get current socket id.
     *
     * @param server
     */
    explicit NetworkSocket(socket_fd_t server) : _server_fd(server), _mode(CHILD) {};

    virtual ~NetworkSocket() = default;
    virtual void init();
    virtual void close();
    virtual void send(void *buffer, size_t length);
    virtual size_t read(void *buffer, size_t length);


    /***********
     * Getters *
     ***********/

    socket_fd_t getId() const;
    std::string const &getIpAddress() const;
    uint16_t getPort() const;
    Mode getMode() const;
    bool isClosed() const;

private:
    std::string _ip;
    uint16_t _port = 0;
    socket_fd_t _server_fd = -1;
    Mode _mode;

    socket_fd_t _id = -1;
    bool _closed = false;

    void create(bool listen);
    void accept();
};


#endif //CPP_INDIE_STUDIO_NETWORKSOCKET_H
