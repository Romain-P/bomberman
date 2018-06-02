//
// Created by romain on 01/06/18.
//

#include <iostream>
#include "ANetworkController.h"

void ANetworkController::init() {
    defineMessageHandlers(_handlers);
}

void ANetworkController::parseMessage(ANetworkClient *client, NetworkMessage *msg) {
    try {
        _handlers.at(static_cast<size_t>(msg->getProtocolId()))(client, msg);
    } catch (std::exception &e) {
        std::cerr << "no handler found for protocol id " << msg->getProtocolId() << std::endl;
        throw std::runtime_error(e.what());
    }
}