//
// Created by Mardel on 30/05/18.
//

#include "BomberWave.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "GameMap.hpp"
#include "GameManager.hpp"
#include <iostream>
#include <Explosion.hpp>
#include <GameUtils.hpp>
#include <PowerUps.hpp>

const std::array<std::string, 4> Player::Characters = {
        "White",
        "Black",
        "Red",
        "Pink"
};

Player::Player(GameManager &manager, int playerNbr, vector2df position, vector2df rotation) :
        GameObject(manager, position, rotation), _bombCount(1), _canPlaceBomb(true), _anim(PLAYERANIM::IDLE), _playerNbr(playerNbr), _score(0)
{
    _tags.push_back(GOTAG::DESTROYABLE);
    for (auto it = _inputs.begin(); it != _inputs.end(); it++)
        (*it) = false;
    Start();
}

MainPlayer::MainPlayer(GameManager &manager, int playerNbr, vector2df position, vector2df rotation) :
        Player(manager, playerNbr, position, rotation), _inputReceiver(_inputs)
{
    _manager.getDevice()->setEventReceiver(&_inputReceiver);
}

void Player::Start()
{
    GameObject::Start();
    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IAnimatedMesh *mesh = device->getSceneManager()->getMesh("resources/models/Character/Bomberman.MD3");
    _node = device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setScale(vector3df(6, 6, 6));
    _node->setRotation(vector3df(0, 0, 0));
    _node->setAnimationSpeed(30);
    _node->setLoopMode(true);
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture(("resources/models/Character/" + Characters[_playerNbr] + "BombermanTextures.png").c_str()));
    _node->setFrameLoop(27, 76);
    UpdatePosition();
}

void Player::Update()
{
    GameObject::Update();
    vector2df movement = GetMovement();

    ApplyBuffs();
    CheckCollisions();
    if (movement != vector2df(0, 0))
    {
        vector2df newPosition = _position + (movement * _manager.getDeltaTime() * _speed);
        if (IsValidPosition(newPosition))
        {
            _node->setRotation(GetRotationFromTo(GameMap::mapToEngine(_position), GameMap::mapToEngine(newPosition)));
            _position = newPosition;
            UpdatePosition();
            PlayAnimation(PLAYERANIM::WALK);
        }
    }
    else
    {
        PlayAnimation(PLAYERANIM::IDLE);
    }
    if (_inputs[(int)PLAYERINPUT::PLACEBOMB] && _canPlaceBomb)
    {
        PlaceBomb();
        _canPlaceBomb = false;
    }
    else if (!_inputs[(int)PLAYERINPUT::PLACEBOMB])
        _canPlaceBomb = true;
}

void Player::CheckCollisions()
{
    std::vector<GOTAG> deathTag(1, GOTAG::DEATH);
    std::vector<GOTAG> powerUpTag(1, GOTAG::POWERUP);
    std::vector<GOTAG> goalTag(1, GOTAG::GOAL);

    if (!_manager.getCollisionsWithTags(*this, deathTag).empty())
    {
        Destroy();
        return;
    }

    auto powerUpCollisions = _manager.getCollisionsWithTags(*this, powerUpTag);
    for (auto it = powerUpCollisions.begin(); it != powerUpCollisions.end(); it++)
    {
        _buffs.push_back(std::unique_ptr<PlayerBuff>((dynamic_cast<PowerUp *>(*it))->GiveBuff(*this)));
        (*it)->Destroy();
    }


    if (!_manager.getCollisionsWithTags(*this, goalTag).empty())
    {
        Destroy();
        return;
    }
}

vector2df Player::GetMovement()
{
    int x = _inputs[(int)PLAYERINPUT::LEFT] ? -1 : _inputs[(int)PLAYERINPUT::RIGHT] ? 1 : 0;
    int y = _inputs[(int)PLAYERINPUT::UP] ? -1 : _inputs[(int)PLAYERINPUT::DOWN] ? 1 : 0;
    return vector2df(x * _speed, y * _speed);
}

bool Player::IsValidPosition(vector2df position)
{
    auto collisions = _manager.getObjectsAtPosition(position);

    if (position.X < 0 || position.Y >= 12 || position.Y < 0 || position.X >= 12)
        return false;
    for (auto it = collisions.begin(); it != collisions.end(); it++)
    {
        auto tags = (*it)->getTags();
        for (auto itTags = tags.begin(); itTags != tags.end(); itTags++)
        {
            if (*itTags == GOTAG::SOLID)
                return false;
        }
    }
    return true;
}

void Player::LateUpdate()
{
    GameObject::LateUpdate();
}

bool Player::UseBombBuff()
{
    for (auto it = _buffs.begin(); it != _buffs.end(); it++)
    {
        if ((*it)->getType() == BUFFTYPE::BOMB)
        {
            _buffs.erase(it);
            return true;
        }
    }
    return false;
}

void Player::PlaceBomb()
{
    if (_bombCount > 0 || UseBombBuff())
    {
        _manager.SpawnObject(new Bomb(_bombPower, *this, _manager, _position, _rotation));
        _bombCount--;
    }
}

void Player::GiveBomb()
{
    _bombCount++;
}

void Player::ApplyBuffs()
{
    _bombPower = BaseBombPower;
    _speed = BaseSpeed;
    for (auto it = _buffs.begin(); it != _buffs.end();)
    {
        (*it)->Apply(_manager.getDeltaTime());
        if ((*it)->getCountDown() == 0)
        {
            it = _buffs.erase(it);
        }
        else
            it++;
    }
}

void Player::UpdatePosition()
{
    _node->setPosition(GameMap::mapToEngine(_position));
}

void Player::PlayAnimation(PLAYERANIM anim)
{
    if (anim != _anim)
    {
        switch (anim)
        {
            case PLAYERANIM::IDLE :
                _node->setFrameLoop(27, 76);
                break;
            case PLAYERANIM::WALK :
                _node->setFrameLoop(0, 26);
                break;
        }
        _anim = anim;
    }
}


PlayerEventReceiver::PlayerEventReceiver(std::array<bool, 6> &inputs) : _inputs(inputs)
{

}

bool PlayerEventReceiver::OnEvent(const irr::SEvent &event)
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