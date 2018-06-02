//
// Created by romain on 02/06/18.
//

#include <HelloConnectMessage.h>
#include <MapDataMessage.h>
#include "GameSessionController.h"

void GameSessionController::defineMessageHandlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::PROTOCOL_ID] = handler(*this, &GameSessionController::onConnect);
}

void GameSessionController::onConnect(GameSession *session, HelloConnectMessage *msg) {
    std::vector<char> data;
    for (size_t i = 0; i < 2000; ++i)
        data.push_back('a');
    session->send(MapDataMessage(data));
}

void GameSessionController::onDisconnect(GameSession *session) {

}
