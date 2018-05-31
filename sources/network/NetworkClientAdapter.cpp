//
// Created by romain on 30/05/18.
//

#include <NetworkProtocol.h>
#include <iostream>
#include "shared/BasicNetworkBuffer.h"
#include "NetworkClientAdapter.h"
#include "shared/NetworkClient.h"

void NetworkClientAdapter::onDataReceived(NetworkClient *client, char const *bytes, size_t length) {
    ANetworkBuffer *buffer = client->getBuffer();

    while (buffer->getPosition() + length >= buffer->getSize())
        if (!parsePacket(client, bytes, length))
            return;

    buffer->append(bytes, length);
}

bool NetworkClientAdapter::parsePacket(NetworkClient *client, const char *&bytes, size_t &length) {
    ANetworkBuffer *buffer = client->getBuffer();

    if (buffer->empty())
        return readNextPacketSize(buffer, bytes, length);

    size_t pos = buffer->getPosition();
    size_t packet_size = buffer->getSize();
    size_t diff = packet_size - pos;

    buffer->append(bytes, diff);
    ANetworkClientAdapter::packetCompleted(client, buffer->getBytes(), buffer->getSize());
    buffer->clear();

    bytes += diff;
    length -= diff;
    return true;
}

bool NetworkClientAdapter::readNextPacketSize(ANetworkBuffer *buffer, char const *&bytes, size_t &length) {
    size_t next_length = NetworkProtocol::packet_length(bytes, length);

    if (!next_length || next_length > NetworkProtocol::PACKET_MAX_SIZE)
        return false;

    buffer->allocate(next_length);
    bytes += NetworkProtocol::HEADER_INT_BYTES;
    length -= NetworkProtocol::HEADER_INT_BYTES;
    return true;
}

std::unique_ptr<ANetworkBuffer> NetworkClientAdapter::bufferFactory() {
    return std::make_unique<BasicNetworkBuffer>(4096);
}
