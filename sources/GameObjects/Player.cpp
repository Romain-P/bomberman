//
// Created by Mardel on 30/05/18.
//

#include "BomberWave.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "GameMap.hpp"
#include "GameManager.hpp"
#include <iostream>

Player::Player(GameManager &manager, vector2df position, vector2df rotation) :
        GameObject(manager, position, rotation), _anim(PLAYERANIM::IDLE), _bombCount(2), _canPlaceBomb(true)
{
    _tags.push_back(GOTAG::DESTROYABLE);
    for (auto it = _inputs.begin(); it != _inputs.end(); it++)
        (*it) = false;
    Start();
}


void Player::Start()
{

}

SoloPlayer::SoloPlayer(GameManager &manager, vector2df position, vector2df rotation) :
        Player(manager, position, rotation), _inputReceiver(_inputs)
{
}

void SoloPlayer::Start()
{
    GameObject::Start();
    irr::IrrlichtDevice *device = dynamic_cast<SoloGameManager &>(_manager).getDevice();
    device->setEventReceiver(&_inputReceiver);

    irr::scene::IAnimatedMesh *mesh = device->getSceneManager()->getMesh("resources/models/Character/Bomberman.MD3");
    _node = device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setScale(vector3df(6, 6, 6));
    _node->setRotation(vector3df(0, 0, 0));
    _node->setAnimationSpeed(30);
    _node->setLoopMode(true);
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture("resources/models/Character/WhiteBombermanTextures.png"));
    _node->setFrameLoop(27, 76);
    UpdatePosition();
}

void Player::Update()
{
    GameObject::Update();
    vector2df movement = GetMovement();

    if (movement != vector2df(0, 0))
    {
        if (IsValidPosition(_position + (movement * _manager.getDeltaTime() * _speed)))
        {
            UpdateRotation(_position, _position + movement * _manager.getDeltaTime() * _speed);
            _position += movement * _manager.getDeltaTime() * _speed;
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
    else
        _canPlaceBomb = true;
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

void SoloPlayer::PlaceBomb()
{
    if (_bombCount > 0)
    {
        _manager.SpawnObject(new SoloBomb(*this, _manager, _position, _rotation));
        _bombCount--;
    }
}

void Player::GiveBomb()
{
    _bombCount++;
}

void SoloPlayer::UpdatePosition()
{
    _node->setPosition(GameMap::mapToEngine(_position));
}

void SoloPlayer::UpdateRotation(vector2df oldpos, vector2df newpos)
{
    vector3df oldEnginePos = GameMap::mapToEngine(oldpos);
    vector3df newEnginePos = GameMap::mapToEngine(newpos);
    vector3df forward = (oldEnginePos - newEnginePos).normalize();
    quaternion current(_node->getRotation());
    quaternion look = LookRotation(forward);
    _node->setRotation(look.getMatrix().getRotationDegrees());
}

quaternion Player::LookRotation(vector3df forward)
{
    vector3df up(0, 1, 0);
    vector3df right = (up.crossProduct(forward)).normalize();
    up = forward.crossProduct(right);
    float m00 = right.X;
    float m01 = right.Y;
    float m02 = right.Z;
    float m10 = up.X;
    float m11 = up.Y;
    float m12 = up.Z;
    float m20 = forward.X;
    float m21 = forward.Y;
    float m22 = forward.Z;

    float num8 = (m00 + m11) + m22;
    quaternion q1;
    if (num8 > 0.0f)
    {
        float num = (float)std::sqrt(num8 + 1.0f);
        q1.W = num + 0.5f;
        num = 0.5f / num;
        q1.X = (m12 - m21) * num;
        q1.Y = (m20 - m02) * num;
        q1.Z = (m01 - m10) * num;

        return q1;
    }
    if ((m00 >= m11) && (m00 >= m22))
    {
        float num7 = (float)std::sqrt(((1.0f + m00) - m11) - m22);
        float num4 = 0.5f / num7;
        q1.X = 0.5f * num7;
        q1.Y = (m01 + m10) * num4;
        q1.Z = (m02 + m20) * num4;
        q1.W = (m12 - m21) * num4;
        return q1;
    }
    if (m11 > m22)
    {
        float num6 = (float)std::sqrt(((1.0f + m11) - m00) - m22);
        float num3 = 0.5F / num6;
        q1.X = (m10 + m01) * num3;
        q1.Y = 0.5f * num6;
        q1.Z = (m21 + m12) * num3;
        q1.W = (m20 - m02) * num3;
        return q1;
    }
    float num5 = (float)std::sqrt(((1.0f + m22) - m00) - m11);
    float num2 = 0.5f / num5;
    q1.X = (m20 + m02) * num2;
    q1.Y = (m21 + m12) * num2;
    q1.Z = 0.5f * num5;
    q1.W = (m01 - m10) * num2;
    return q1;
}

void SoloPlayer::PlayAnimation(PLAYERANIM anim)
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