//
// Created by romain on 02/06/18.
//

#include <HelloConnectMessage.h>
#include "GameSessionController.h"

void GameSessionController::defineMessageHandlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::PROTOCOL_ID] = handler(*this, &GameSessionController::onConnect);
}

void GameSessionController::onConnect(GameSession *session, HelloConnectMessage *msg) {

}

void GameSessionController::onDisconnect(GameSession *session) {

}
