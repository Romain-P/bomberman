//
// Created by romain on 02/06/18.
//

#include <iostream>
#include "GameSessionHandler.h"

void GameSessionHandler::onConnect(NetworkClient *client) {
    std::cerr << "[Session] connected" << std::endl;
}

void GameSessionHandler::onReceive(NetworkClient *client, char const *buffer, size_t length) {
    auto msg = _session->receive(buffer, length);
    std::cerr << "[Session] recv\t<--\t\t" << msg.get() << std::endl;
    _controller.parseMessage(_session, msg.get());
}

void GameSessionHandler::onSent(NetworkClient *client, char const *buffer, size_t length) {
    auto msg = _session->receive(buffer, length);
    std::cerr << "[Session] sent\t-->\t\t" << msg.get() << std::endl;
}

void GameSessionHandler::onDisconnect(NetworkClient *client) {
    _controller.onDisconnect(_session);
    std::cerr << "[Session] disconnected";
}