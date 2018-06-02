//
// Created by romain on 01/06/18.
//

#include <iostream>
#include "ANetworkClient.h"

void ANetworkClient::send(NetworkMessage const &message) {
    _writer.clear();
    NetworkProtocol::serialize(message, _writer);
    _client->send(_writer.getBytes(), _writer.getSize());
}

std::unique_ptr<NetworkMessage> ANetworkClient::receive(char const *bytes, size_t length) {
    _reader.clear();
    _reader.append(bytes, length);
    _reader.setPosition(0);
    return NetworkProtocol::deserialize(_reader);
}

void ANetworkClient::kick(bool force) {
    _client->close(force);
}

size_t ANetworkClient::getId() const {
    return static_cast<size_t>(_client->getId());
}