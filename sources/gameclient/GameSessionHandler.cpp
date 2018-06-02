//
// Created by romain on 02/06/18.
//

#include <iostream>
#include <sstream>
#include "GameSessionHandler.h"

void GameSessionHandler::onConnect(NetworkClient *client) {
    log("[Session] connected\n");
}

void GameSessionHandler::onReceive(NetworkClient *client, char const *buffer, size_t length) {
    while (!_session);

    auto msg = _session->receive(buffer, length);

    std::ostringstream s;
    s << *msg;
    log("[Session] recv\t\t\t<--\t\t[Server]:\t\t%s\n", s.str().c_str());

    _controller.parseMessage(_session, msg.get());
}

void GameSessionHandler::onSent(NetworkClient *client, char const *buffer, size_t length) {

    buffer += NetworkProtocol::HEADER_INT_BYTES;
    length -= NetworkProtocol::HEADER_INT_BYTES;

    auto msg = _session->receive(buffer, length);

    std::ostringstream s;
    s << *msg;
    log("[Session] sent\t\t\t-->\t\t|Server]:\t\t%s\n", s.str().c_str());
}

void GameSessionHandler::onDisconnect(NetworkClient *client) {
    _controller.onDisconnect(_session);
    log("[Session] disconnected\n");
}

void GameSessionHandler::setSession(GameSession *session) {
    _session = session;
}
