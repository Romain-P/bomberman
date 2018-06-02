//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKASYNCSERVER_H
#define CPP_INDIE_STUDIO_NETWORKASYNCSERVER_H


#include <shared/ANetworkAsyncListener.h>
#include <unordered_map>
#include <memory>
#include "shared/NetworkClient.h"
#include "shared/INetworkClientHandler.h"

using clients_t = std::unordered_map<socket_fd_t, std::unique_ptr<NetworkClient>>;

class ANetworkAsyncServer: public NetworkAsyncListener {
friend class NetworkClient;

public:

    ANetworkAsyncServer(std::string const &ip, uint16_t port) : NetworkAsyncListener(),
            _socket(ip, port, NetworkSocket::PASSIVE),
            _clients(),
            _adapter()
    {}

    void start() override;
    void close() override;

    uint16_t getPort();

protected:

    /**
     * Adapter for buffer type, read size, client handler..
     */
    virtual std::unique_ptr<ANetworkClientAdapter> defineClientAdapter() = 0;

    virtual void onServerClosed() = 0;

private:

    NetworkSocket _socket;
    clients_t _clients;
    std::unique_ptr<ANetworkClientAdapter> _adapter;

    void onListenerClosed(bool interrupted) final;
    socket_fd_t defineServerFd() final;
    void onSocketNotified(socket_fd_t socket) final;
};


#endif //CPP_INDIE_STUDIO_NETWORKASYNCSERVER_H
