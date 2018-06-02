//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_INETWORKADAPTER_H
#define CPP_INDIE_STUDIO_INETWORKADAPTER_H

#include <sys/types.h>
#include <memory>
#include "shared/INetworkClientHandler.h"
#include "shared/ANetworkBuffer.h"

class NetworkClient;

class ANetworkClientAdapter {
public:

    explicit ANetworkClientAdapter(size_t readSize, INetworkClientHandler *handler) : _readSize(readSize), _handler(handler) {}
    virtual ~ANetworkClientAdapter() = default;

    /**
     * Implement this method to parse network received bytes,
     * i.e parsing rules, delimiter etc..
     *
     * @param client    network client receiving the data
     * @param buffer    received bytes
     * @param length    buffer bytes count
     */
    virtual void onDataReceived(NetworkClient *client, char const *buffer, size_t length) = 0;

    /**
     * Provide a buffer implementation, used for each client.
     */
    virtual std::unique_ptr<ANetworkBuffer> bufferFactory() = 0;

    INetworkClientHandler *getHandler();
    size_t readSize() const;

protected:

    /**
     * Call this method when a packet is completed.
     * Then the bytes are sent to the onReceived handler method of the client.
     *
     * @param client    network client receiving the packet
     */
    void packetCompleted(NetworkClient *client, char const *bytes, size_t length);

private:

    size_t _readSize;
    INetworkClientHandler *_handler;
};

#endif //CPP_INDIE_STUDIO_INETWORKADAPTER_H
