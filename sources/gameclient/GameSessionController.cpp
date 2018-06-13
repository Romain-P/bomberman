//
// Created by romain on 02/06/18.
//

#include <HelloConnectMessage.h>
#include <GameDataMessage.h>
#include <RequestLobbyMessage.h>
#include "GameSessionController.h"
#include "GameManager.hpp"

void GameSessionController::defineMessageHandlers(handlers_t &handlers)
{
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
    if (_lobby == nullptr)
    {
        _lobby = std::make_unique<GameLobby>(session, msg->getReadyPlayers() - 1);
        _lobbyThread = _lobby->EnterLobby();
    }
    _lobby->Update(msg->getReadyPlayers());
    _lobby->Draw();
}

//start the game here
void GameSessionController::loadGameData(GameSession *session, GameDataMessage *msg)
{
    _lobby->StopLobby();
    _lobbyThread.join();
    _manager = std::make_unique<NetworkGameManager>(session);
    _manager->setMap(msg->getMap());
    auto infos = msg->getPlayerInformations();
    for (auto it = infos.begin(); it != infos.end(); it++)
    {
        _manager->getPlayers()[it->playerNbr] = std::make_unique<Player>(*_manager, it->playerNbr, vector2df(it->x, it->y));
        if (it->clientId == session->getId())
            _manager->setLocalPlayerNbr(it->playerNbr);
    }
    _gameThread = _manager->StartThread();
}

void GameSessionController::onInputReceived(GameSession *session, InputMessage *msg)
{
    if (_manager != nullptr)
    {
        size_t playerId = msg->getPlayerId();
        PLAYERINPUT input = msg->getType();
        bool status = msg->getStatus();
        _manager->getPlayers()[playerId]->getInputs()[(int)input] = status;
    }
}

void GameSessionController::poll() {
    lock_t lock(_locker);

    if (_waiting.empty()) return;

    Waiting &waiting = _waiting.at(0);

    parseMessage(waiting.client, waiting.msg.get());
    _waiting.pop_front();
}

void GameSessionController::add(GameSession *client, std::unique_ptr<NetworkMessage> &msg) {
    lock_t lock(_locker);

    _waiting.push_back({client, std::move(msg)});
}