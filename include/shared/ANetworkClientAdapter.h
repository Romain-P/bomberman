//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_INETWORKADAPTER_H
#define CPP_INDIE_STUDIO_INETWORKADAPTER_H

#include <sys/types.h>
#include <shared/NetworkClient.h>
#include <memory>
#include "ANetworkBuffer.h"
#include "INetworkClientHandler.h"

class NetworkClient;

class ANetworkClientAdapter {
public:

    explicit ANetworkClientAdapter(size_t readSize) : _readSize(readSize), _handler() {}
    virtual ~ANetworkClientAdapter() = default;

    virtual void onDataReceived(NetworkClient *client, char *buffer, size_t length) = 0;
    virtual std::unique_ptr<ANetworkBuffer> bufferFactory() = 0;

    inline INetworkClientHandler *getHandler() {
        if (_handler == nullptr)
            _handler = std::move(defineClientHandler());

        return _handler.get();
    }

    inline size_t readSize() const {
        return _readSize;
    }

protected:

    virtual std::unique_ptr<INetworkClientHandler> defineClientHandler() = 0;

private:

    size_t _readSize;
    std::unique_ptr<INetworkClientHandler> _handler;
};

#endif //CPP_INDIE_STUDIO_INETWORKADAPTER_H
