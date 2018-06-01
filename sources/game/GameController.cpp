//
// Created by romain on 01/06/18.
//

#include "HelloConnectMessage.h"
#include "GameController.h"

void GameController::defineMessageHandlers(handlers_t &handlers) {
    handlers[MapDataMessage::PROTOCOL_ID] = handler(*this, &GameController::onMapDataMessage);
}

void GameController::onConnect(GameClient *client) {
    client->send(HelloConnectMessage());
}

void GameController::onDisconnect(GameClient *client) {

}

void GameController::onMapDataMessage(GameClient *client, MapDataMessage *msg) {

}