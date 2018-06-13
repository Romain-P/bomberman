//
// Created by Mardel on 10/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMELOBBY_HPP
#define CPP_INDIE_STUDIO_GAMELOBBY_HPP

#include <irrlicht.h>
#include <map>
#include "GameSessionController.h"

enum class LOBBYCHOICE
{
    NONE = 101,
    PLAY,
    LEAVE
};

class LobbyEventReceiver : public irr::IEventReceiver
{
public:
    LobbyEventReceiver(LOBBYCHOICE &lobbyChoice);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    LOBBYCHOICE &_lobbyChoice;
};

class GameLobby
{
public:
    GameLobby(GameSessionController &controller, GameSession *session, int _playerId);
    bool Run();
    void Draw();
    void Update(int playerCount);
    void StopLobby();
    void Start();
private:
    void setPlayerCount(int count);
    int getPlayerCount();
    bool getUpdate();
    void setUpdate(bool update);
    GameSessionController &_controller;
    GameSession *_session;
    LOBBYCHOICE _lobbyChoice;
    LobbyEventReceiver _eventReceiver;
    int _playerCount;
    int _playerId;
    bool _update;
    bool _gameStarted;
};

#endif //CPP_INDIE_STUDIO_GAMELOBBY_HPP
