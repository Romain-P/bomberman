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

void GameLobby::Start()
{
    Device->setEventReceiver(&_eventReceiver);
    Device->getSceneManager()->addLightSceneNode(0, core::vector3df(0, 20, 0), irr::video::SColorf(1, 1, 1));
    Device->getSceneManager()->setAmbientLight(irr::video::SColor(0, 160, 160, 160));
    irr::scene::ICameraSceneNode *camera = Device->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(-50, 40, 0));
    camera->setTarget(irr::core::vector3df(0, 40, 0));
    _lobbyChoice = LOBBYCHOICE::NONE;
}

bool GameLobby::Run()
{
        if (Device->isWindowActive())
        {
            Device->getVideoDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
            Draw();
            if (_lobbyChoice == LOBBYCHOICE::PLAY)
            {
                _session->send(RequestStartGameMessage());
            }
            Device->getVideoDriver()->endScene();
            if (_lobbyChoice == LOBBYCHOICE::LEAVE)
                return false;
        }
        return true;
}

void GameLobby::StopLobby()
{
    Device->getSceneManager()->clear();
    Device->getGUIEnvironment()->clear();
}

void GameLobby::Update(int playerCount)
{
    std::cout << "Update Lobby with : " << playerCount << " players" << std::endl;
    setPlayerCount(playerCount);
    setUpdate(true);
    Device->getSceneManager()->clear();
    Device->getGUIEnvironment()->clear();
    for (int i = 0; i < 4; i++)
    {
        irr::scene::IMesh *mesh = Device->getSceneManager()->getMesh("resources/models/Pillar/Pillar.obj");
        irr::scene::IMeshSceneNode *node = Device->getSceneManager()->addMeshSceneNode(mesh);
        node->setPosition(irr::core::vector3df(0, 20, 40 - (20 * i)));
        node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("resources/models/Pillar/Pillar.jpg"));
    }
    for (int i = 0; i < _playerCount; i++)
    {
        irr::scene::IAnimatedMesh *mesh = Device->getSceneManager()->getMesh("resources/models/Character/Bomberman.MD3");
        irr::scene::IAnimatedMeshSceneNode *node = Device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
        node->setPosition(irr::core::vector3df(0, 40, 40 - (20 * i)));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setScale(irr::core::vector3df(6, 6, 6));
        node->setRotation(irr::core::vector3df(0, 90, 0));
        node->setAnimationSpeed(30);
        node->setFrameLoop(27, 76);
        node->setLoopMode(true);
        node->setMaterialTexture(0, Device->getVideoDriver()->getTexture(("resources/models/Character/" + Player::Characters[i] + "BombermanTextures.png").c_str()));
    }
    if (_playerId == 0)
    {
        Device->getGUIEnvironment()->addButton(rect<s32>(1920 / 2 - 100, 800, 1920 / 2 + 100,  1000), nullptr, (int)LOBBYCHOICE::PLAY,
                                               L"Launch Game", L"Launch The Game");
    }
    Device->getGUIEnvironment()->addButton(rect<s32>(1920 / 2 + 200, 800, 1920 / 2 + 400,  1000), nullptr, (int)LOBBYCHOICE::LEAVE,
                                           L"Leave", L"Leave lobby");
}

void GameLobby::Draw()
{
    Device->getSceneManager()->drawAll();
    Device->getGUIEnvironment()->drawAll();
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