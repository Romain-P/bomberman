//
// Created by Mardel on 28/05/18.
//

#include "GameManager.hpp"
#include <iostream>
#include <Walls.hpp>
#include <GameMapFactory.h>
#include <thread>
#include <Explosion.hpp>
#include <Monster.hpp>
#include <PowerUps.hpp>
#include <GameUIManager.hpp>
#include <BomberWave.hpp>

GameManager::GameManager(GAMETYPE gameType) :
        _time(), _gameRunning(false), _currentId(0), _level(1), _gameWon(false)
{
    if (gameType != GAMETYPE::PVP)
    {
        _players[0] = std::unique_ptr<Player>(new Player(*this, 0));
        if (gameType == GAMETYPE::DUO)
        {
            _players[1] = std::unique_ptr<Player>(new Player(*this, 1));
            _eventReceiver = std::make_unique<DuoGameEventReceiver>(_players[0]->getInputs(), _players[1]->getInputs());
        }
        else
            _eventReceiver = std::make_unique<GameEventReceiver>(_players[0]->getInputs());
        Device->setEventReceiver(_eventReceiver.get());
    }
}


void GameManager::LoadMap()
{
    GameDataSerializer serializer;
    GameMapFactory factory(serializer);

    _map = factory.loadByTemplate(std::to_string(_level));
}


NetworkGameManager::NetworkGameManager(GameSessionController &controller, GameSession *session) : GameManager(GAMETYPE::PVP), _controller(controller), _session(session), _localPlayerNbr(0)
{

}

void GameManager::SpawnMapObjects()
{
    for (int y = 0; y < GameMap::MapSize; y++)
    {
        for (int x = 0; x < GameMap::MapSize; x++)
        {
            int spot = _map->getMapPosition(x, y);
            if (spot == GameMap::CellType::WALL)
            {
                SpawnObject(new Wall(*this, vector2df(x, y)));
            }
            else if (spot == GameMap::CellType::BREAKABLE_WALL)
            {
                SpawnObject(new DestroyableWall(*this, vector2df(x, y)));
            }
            else if (spot == GameMap::CellType::ENEMY_SPAWN)
            {
                SpawnObject(new Goal(*this, vector2df(x, y)));
            }
        }
    }
    for (int i = 0; i < _map->getEnemyCount(); i++)
    {
        SpawnObject(new Monster(*this, _map->getGoal()));
    }
}

void NetworkGameManager::LaunchGame()
{
    _eventReceiver = std::make_unique<NetworkGameEventReceiver>(_players[_localPlayerNbr]->getInputs(), _session);
    _uiManager = std::unique_ptr<GameUIManager>(new NetworkGameUIManager(*this, _localPlayerNbr));
    LaunchLevel();
    Device->getSceneManager()->clear();
}

std::thread NetworkGameManager::StartThread()
{
    return std::thread([this] { this->LaunchGame();});
}

void GameManager::LaunchGame()
{
    _uiManager = std::unique_ptr<GameUIManager>(new GameUIManager(*this));
    while (_level < 3)
    {
        LoadMap();
        LaunchLevel();
        _level++;
        if (!_gameWon)
            return;
        _gameWon = false;
    }
    Device->getSceneManager()->clear();
}

void GameManager::Win()
{
    _gameWon = true;
}

void GameManager::LaunchLevel()
{
    _gameRunning = true;
    _bgLoader.LoadRandomBackground();
    _bgLoader.LoadRandomTerrain();
    for (auto it = _players.begin(); it != _players.end(); it++)
        it->second->setPosition(_map->getPlayerSpawns()[0]);
    SpawnMapObjects();
    _time.Reset();
    while (_gameRunning && Device->run() && !GameOver() & !_gameWon)
    {
        _uiManager->UpdateUI();
        RunUpdates();
        RenderGame();
        RemoveDestroyed();
    }
    Cleanup();
    RemoveDestroyed();
}

bool GameManager::GameOver()
{
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if (!it->second->shouldBeDestroyed())
            return false;
    }
    return true;
}

void GameManager::RemoveDestroyed()
{
    for (auto it = _objects.begin(); it != _objects.end();)
    {
        if ((*it)->shouldBeDestroyed())
            it = _objects.erase(it);
        else
            ++it;
    }
}

void GameManager::Cleanup()
{
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        (*it)->Destroy();
    }
    Device->getGUIEnvironment()->clear();
}

void GameManager::RunUpdates()
{
    _time.Update();
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if (!it->second->shouldBeDestroyed())
        {
            it->second->Update();
        }
    }
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        if (!(*it)->shouldBeDestroyed())
            (*it)->Update();
    }
}

void NetworkGameManager::RunUpdates()
{
    _controller.poll();
    GameManager::RunUpdates();
}

float GameManager::getDeltaTime()
{
    return _time.getDeltaTime();
}

void GameManager::RenderGame()
{
    _renderer.Render();
}

int GameManager::GenerateId()
{
    _currentId++;
    return _currentId;
}

void GameManager::SpawnObject(GameObject *object)
{
    _objects.emplace_back(std::unique_ptr<GameObject>(object));
}

std::vector<GameObject *> GameManager::getObjectsAtPosition(vector2df position)
{
    std::vector<GameObject *> objects;

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        if ((int)position.X == (int)(*it)->getPosition().X && (int)position.Y == (int)(*it)->getPosition().Y)
        {
            objects.push_back((*it).get());
        }
    }
    return objects;
}


std::vector<GameObject *> GameManager::getCollisionsWithTags(GameObject &object, std::vector<GOTAG> &tags)
{
    std::vector<GameObject *> objects;

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        if ((int)object.getPosition().X == (int)(*it)->getPosition().X && (int)object.getPosition().Y == (int)(*it)->getPosition().Y)
        {
            if (tags.empty() && (*it)->getId() != object.getId())
                objects.push_back((*it).get());
            else
            {
                for (auto tagsIt = tags.begin(); tagsIt != tags.end(); tagsIt++)
                {
                    if (object.getId() != (*it)->getId() && (*it)->HasTag(*tagsIt))
                    {
                        objects.push_back((*it).get());
                        break;
                    }
                }
            }
        }
    }
    return objects;
}

GameManager::~GameManager() {

}

GameEventReceiver::GameEventReceiver(std::array<bool, 6> &inputs) : _inputs(inputs)
{

}

bool GameEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch(event.KeyInput.Key)
        {
            case KEY_ESCAPE:
                _inputs[(int)PLAYERINPUT::PAUSE] = event.KeyInput.PressedDown;
                break;
            case KEY_SPACE:
                _inputs[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                break;
            case KEY_UP:
            case KEY_KEY_Z:
                _inputs[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                break;
            case KEY_DOWN:
            case KEY_KEY_S:
                _inputs[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                break;
            case KEY_LEFT:
            case KEY_KEY_Q:
                _inputs[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                break;
            case KEY_RIGHT:
            case KEY_KEY_D:
                _inputs[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                break;
            default:
                break;
        }
    }
    return false;
}

NetworkGameEventReceiver::NetworkGameEventReceiver(std::array<bool, 6> &inputs, GameSession *session) : _inputs(inputs), _session(session)
{

}

bool NetworkGameEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch(event.KeyInput.Key)
        {
            case KEY_ESCAPE:
                _inputs[(int)PLAYERINPUT::PAUSE] = event.KeyInput.PressedDown;
                _session->send(InputMessage(PLAYERINPUT::PAUSE, event.KeyInput.PressedDown, _session->getId()));
                break;
            case KEY_SPACE:
                _inputs[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                _session->send(InputMessage(PLAYERINPUT::PLACEBOMB, event.KeyInput.PressedDown, _session->getId()));
                break;
            case KEY_UP:
            case KEY_KEY_Z:
                _inputs[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                _session->send(InputMessage(PLAYERINPUT::UP, event.KeyInput.PressedDown, _session->getId()));
                break;
            case KEY_DOWN:
            case KEY_KEY_S:
                _inputs[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                _session->send(InputMessage(PLAYERINPUT::DOWN, event.KeyInput.PressedDown, _session->getId()));
                break;
            case KEY_LEFT:
            case KEY_KEY_Q:
                _inputs[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                _session->send(InputMessage(PLAYERINPUT::LEFT, event.KeyInput.PressedDown, _session->getId()));
                break;
            case KEY_RIGHT:
            case KEY_KEY_D:
                _inputs[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                _session->send(InputMessage(PLAYERINPUT::RIGHT, event.KeyInput.PressedDown, _session->getId()));
                break;
            default:
                break;
        }
    }
    return false;
}

DuoGameEventReceiver::DuoGameEventReceiver(std::array<bool, 6> &inputs,std::array<bool, 6> &inputstwo) : _inputs(inputs), _inputstwo(inputstwo)
{

}

bool DuoGameEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch(event.KeyInput.Key)
        {
            case KEY_ESCAPE:
                _inputs[(int)PLAYERINPUT::PAUSE] = event.KeyInput.PressedDown;
                break;
            case KEY_SPACE:
                _inputs[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                break;
            case KEY_END:
                _inputstwo[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                break;
            case KEY_UP:
                _inputstwo[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_Z:
                _inputs[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                break;
            case KEY_DOWN:
                _inputstwo[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_S:
                _inputs[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                break;
            case KEY_LEFT:
                _inputstwo[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_Q:
                _inputs[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                break;
            case KEY_RIGHT:
                _inputstwo[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_D:
                _inputs[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                break;
            default:
                break;
        }
    }
    return false;
}