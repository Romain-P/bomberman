//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKASYNCSERVER_H
#define CPP_INDIE_STUDIO_NETWORKASYNCSERVER_H


#include <shared/ANetworkAsyncListener.h>
#include <unordered_map>
#include <memory>
#include "NetworkClient.h"
#include "INetworkClientHandler.h"

using clients_t = std::unordered_map<socket_fd_t, std::unique_ptr<NetworkClient>>;

class NetworkAsyncServer: public NetworkAsyncListener {
public:

    NetworkAsyncServer(std::string const &ip, uint16_t port) : NetworkAsyncListener(),
            _socket(ip, port, NetworkSocket::PASSIVE),
            _clients(),
            _adapter()
    {}
    virtual ~NetworkAsyncServer() = default;

    void start() override;
    void close() override;

    clients_t &getClients();

protected:

    /**
     * Adapter for buffer type, read size, client handler..
     */
    virtual std::unique_ptr<ANetworkClientAdapter> defineClientAdapter() = 0;

    void onSocketNotified(socket_fd_t socket) override;

private:

    NetworkSocket _socket;
    clients_t _clients;
    std::unique_ptr<ANetworkClientAdapter> _adapter;

    void onListenerClosed(bool interrupted) final;
    socket_fd_t defineServerFd() final;
};


#endif //CPP_INDIE_STUDIO_NETWORKASYNCSERVER_H
