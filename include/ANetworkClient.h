//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_ANETWORKCLIENT_H
#define CPP_INDIE_STUDIO_ANETWORKCLIENT_H


#include <shared/NetworkClient.h>
#include "BinaryDataReader.h"
#include "BinaryDataWriter.h"
#include "NetworkMessage.h"

class ANetworkClient {
public:
    explicit ANetworkClient(NetworkClient *client) : _client(client), _reader(), _writer() {}

    virtual void send(NetworkMessage const &message);
    virtual std::unique_ptr<NetworkMessage> receive(char const *bytes, size_t length);

    void kick(bool force = false);
    virtual size_t getId() const;

private:

    NetworkClient *_client;
    BinaryDataReader _reader;
    BinaryDataWriter _writer;
};


#endif //CPP_INDIE_STUDIO_ANETWORKCLIENT_H
