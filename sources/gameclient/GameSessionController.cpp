//
// Created by romain on 02/06/18.
//

#include <HelloConnectMessage.h>
#include <GameDataMessage.h>
#include <RequestLobbyMessage.h>
#include "GameSessionController.h"

void GameSessionController::defineMessageHandlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::PROTOCOL_ID] = handler(*this, &GameSessionController::onConnect);
    handlers[LobbyUpdateMessage::PROTOCOL_ID] = handler(*this, &GameSessionController::onLobbyUpdated);
    handlers[GameDataMessage::PROTOCOL_ID] = handler(*this, &GameSessionController::loadGameData);
    handlers[InputMessage::PROTOCOL_ID] = handler(*this, &GameSessionController::onInputReceived);
}

void GameSessionController::onConnect(GameSession *session, HelloConnectMessage *msg)
{
    session->send(RequestLobbyMessage());
}

void GameSessionController::onDisconnect(GameSession *session)
{

}

void GameSessionController::onLobbyUpdated(GameSession *session, LobbyUpdateMessage *msg)
{
    msg->getMaxPlayers();
    msg->getReadyPlayers();
}

//start the game here
void GameSessionController::loadGameData(GameSession *session, GameDataMessage *msg) {
    msg->getMap(); //game map
    msg->getPlayerInformations(); //contains spawn position for each player
}

void GameSessionController::onInputReceived(GameSession *session, InputMessage *msg) {
    msg->getPlayerId(); //player who pressed/released an input
    msg->getType(); //input type @see message enum
    msg->getStatus(); // input down / up
}
