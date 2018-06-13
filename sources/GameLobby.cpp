//
// Created by Mardel on 10/06/18.
//

#include <Player.hpp>
#include <BomberWave.hpp>
#include <shared_mutex>
#include "GameLobby.hpp"

GameLobby::GameLobby(GameSessionController &controller, GameSession *session, int playerId) : _controller(controller), _session(session), _lobbyChoice(LOBBYCHOICE::NONE), _eventReceiver(_lobbyChoice), _playerId(playerId), _gameStarted(false)
{
}

void GameLobby::Run()
{
    Device->setEventReceiver(&_eventReceiver);
    Device->getSceneManager()->addLightSceneNode(0, core::vector3df(0, 20, 0), irr::video::SColorf(1, 1, 1));
    Device->getSceneManager()->setAmbientLight(irr::video::SColor(0, 160, 160, 160));
    irr::scene::ICameraSceneNode *camera = Device->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(-50, 40, 0));
    camera->setTarget(irr::core::vector3df(0, 40, 0));
    _lobbyChoice = LOBBYCHOICE::NONE;
    while (Device->run() && !_gameStarted)
    {
        if (Device->isWindowActive())
        {
                if (_lobbyChoice == LOBBYCHOICE::PLAY)
                {
                    _session->send(RequestStartGameMessage());
                    return;
                }
                _controller.poll();
        }
    }
}

void GameLobby::StopLobby()
{
    _gameStarted = true;
}

void GameLobby::Update(int playerCount)
{
    setPlayerCount(playerCount);
    setUpdate(true);
}

void GameLobby::Draw()
{
    Device->getVideoDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
    for (int i = 0; i < 4; i++)
    {
        irr::scene::IMesh *mesh = Device->getSceneManager()->getMesh("resources/models/Pillar/Pillar.obj");
        irr::scene::IMeshSceneNode *node = Device->getSceneManager()->addMeshSceneNode(mesh);
        node->setPosition(irr::core::vector3df(-80 + (80 * i), 20, 0));
        node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("resources/models/Pillar/Pillar.jpg"));
    }
    for (int i = 0; i < _playerCount; i++)
    {
        irr::scene::IAnimatedMesh *mesh = Device->getSceneManager()->getMesh("resources/models/Character/Bomberman.MD3");
        irr::scene::IAnimatedMeshSceneNode *node = Device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
        node->setPosition(irr::core::vector3df(-80 + (80 * i), 40, 0));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setScale(irr::core::vector3df(6, 6, 6));
        node->setRotation(irr::core::vector3df(0, 0, 0));
        node->setAnimationSpeed(30);
        node->setLoopMode(true);
        node->setMaterialTexture(0, Device->getVideoDriver()->getTexture(("resources/models/Character/" + Player::Characters[i] + "BombermanTextures.png").c_str()));
    }
    Device->getSceneManager()->drawAll();
    Device->getGUIEnvironment()->drawAll();
    Device->getVideoDriver()->endScene();
}

void GameLobby::setPlayerCount(int count)
{
    _playerCount = count;
}

int GameLobby::getPlayerCount()
{
    return _playerCount;
}

bool GameLobby::getUpdate()
{
    return _update;
}

void GameLobby::setUpdate(bool update)
{
    _update = update;
}

LobbyEventReceiver::LobbyEventReceiver(LOBBYCHOICE &lobbyChoice) : _lobbyChoice(lobbyChoice)
{

}

bool LobbyEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        switch(event.GUIEvent.EventType)
        {
            case EGET_BUTTON_CLICKED:
                switch((LOBBYCHOICE)id)
                {
                    case LOBBYCHOICE::PLAY :
                        _lobbyChoice = LOBBYCHOICE::PLAY;
                        break;
                    case LOBBYCHOICE::LEAVE :
                        _lobbyChoice = LOBBYCHOICE::LEAVE;
                        break;
                    case LOBBYCHOICE::NONE :
                        _lobbyChoice = LOBBYCHOICE::NONE;
                        break;
                }
                break;
            default:
                break;
        }
    }
    return false;
}