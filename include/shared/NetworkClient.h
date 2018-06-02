//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKCLIENT_H
#define CPP_INDIE_STUDIO_NETWORKCLIENT_H


#include "shared/NetworkSocket.h"
#include "shared/ANetworkBuffer.h"
#include "shared/ANetworkClientAdapter.h"

class NetworkClient {

public:

    NetworkClient(std::string const &ip, uint16_t port, ANetworkClientAdapter *adapter)
            : _socket(ip, port, NetworkSocket::ACTIVE),
              _adapter(adapter),
              _closed(false)
    {};

    NetworkClient(socket_fd_t serverSocketFd, ANetworkClientAdapter *adapter)
            : _socket(serverSocketFd),
              _adapter(adapter),
              _closed(false)
    {};

    void init();
    void read();
    void send(char *buffer, size_t length);
    ANetworkClientAdapter *getAdapter();
    ANetworkBuffer *getBuffer();
    socket_fd_t getId() const;
    bool isClosed() const;

    /**
     * Close the network client
     *
     * @param force     true to close the socket manually, if no wrapper exists (e.g server)
     */
    void close(bool force = false);

private:

    NetworkSocket _socket;
    ANetworkClientAdapter *_adapter;
    std::unique_ptr<ANetworkBuffer> _buffer;
    bool _closed;
};


#endif //CPP_INDIE_STUDIO_NETWORKCLIENT_H
