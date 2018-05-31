//
// Created by romain on 31/05/18.
//

#include "shared/ANetworkClientAdapter.h"
#include "shared/NetworkClient.h"
#include <cstring>
#include <iostream>

void ANetworkClientAdapter::packetCompleted(NetworkClient *client, size_t from, size_t to, bool drop) {
    size_t packet_len = to - from + 1;
    char packet[packet_len];

    if (from > client->getBuffer()->getSize())
        std::cerr << "ANetworkClientAdapter::packetCompleted: base address > buffer size" << std::endl;
    else {
        strncpy(packet, client->getBuffer()->getBytes() + from, packet_len);
        client->getAdapter()->getHandler()->onReceive(client, packet, packet_len);

        if (!drop) return;

        char remaining[client->getBuffer()->getSize() - packet_len];

    }
}

INetworkClientHandler *ANetworkClientAdapter::getHandler() {
    return _handler;
}

size_t ANetworkClientAdapter::readSize() const {
    return _readSize;
}
