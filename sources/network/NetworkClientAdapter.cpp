//
// Created by romain on 30/05/18.
//

#include "shared/BasicNetworkBuffer.h"
#include "NetworkClientAdapter.h"
#include "shared/NetworkClient.h"

void NetworkClientAdapter::onDataReceived(NetworkClient *client, char const *buffer, size_t length) {
    if (client->getBuffer()->empty()) {

    }
}

std::unique_ptr<ANetworkBuffer> NetworkClientAdapter::bufferFactory() {
    return std::make_unique<BasicNetworkBuffer>(4096);
}
