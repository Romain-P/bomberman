//
// Created by romain on 31/05/18.
//

#include "shared/ANetworkClientAdapter.h"
#include "shared/NetworkClient.h"
#include <cstring>
#include <iostream>

void ANetworkClientAdapter::packetCompleted(NetworkClient *client, char const *bytes, size_t length) {
    client->getAdapter()->getHandler()->onReceive(client, bytes, length);
}

INetworkClientHandler *ANetworkClientAdapter::getHandler() {
    return _handler;
}

size_t ANetworkClientAdapter::readSize() const {
    return _readSize;
}
