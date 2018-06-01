//
// Created by Mardel on 30/05/18.
//

#include <BomberWave.hpp>
#include <Bomb.hpp>
#include "Player.hpp"

Player::Player(GameManager &manager) : GameObject(manager), (PLAYERINPUT::NONE), _inputReceiver(_input)
{

}

void Player::Start()
{
    GameObject::Start();
}

void Player::Update()
{
    GameObject::Update();
    vector3df movement = GetMovement();

    if (movement != vector3df(0,0,0))
    {
        if (IsValidPosition(_position + (movement * BomberWave::Time.getDeltaTime())))
            _position += movement * BomberWave::Time.getDeltaTime();
    }
    if (_input == PLAYERINPUT::PLACEBOMB)
        PlaceBomb();
}

vector3df Player::GetMovement()
{
    int x = _input == PLAYERINPUT::LEFT ? -1 : _input == PLAYERINPUT::RIGHT ? 1 : 0;
    int y = _input == PLAYERINPUT::DOWN ? -1 : _input == PLAYERINPUT::UP ? 1 : 0;
    return (vector3df(x * _speed, y * _speed, 0));
}

bool Player::IsValidPosition(vector3df position)
{
    const GameMap &map = _manager.getMap();

    if (map.getMapPosition((int)position.X, (int)position.Y) != 0)
        return (false);
    return true;
}

void Player::LateUpdate()
{
    GameObject::LateUpdate();
}

void Player::PlaceBomb()
{
    if (_bombCount > 0)
    {
        _manager.SpawnObject(std::move(Bomb(_manager, _position, _rotation)));
        _bombCount--;
    }
}

void Player::GiveBomb()
{
    _bombCount++;
}

PlayerEventReceiver::PlayerEventReceiver(PLAYERINPUT &playerInput) : _playerInput(playerInput)
{

}

bool PlayerEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch(event.KeyInput.Key)
        {
            case KEY_ESCAPE:
                _playerInput = PLAYERINPUT::PAUSE;
                break;
            case KEY_SPACE:
                _playerInput = PLAYERINPUT::PLACEBOMB;
                break;
            case KEY_UP:
            case KEY_KEY_Z:
                _playerInput = PLAYERINPUT::UP;
                break;
            case KEY_DOWN:
            case KEY_KEY_S:
                _playerInput = PLAYERINPUT::DOWN;
                break;
            case KEY_LEFT:
            case KEY_KEY_Q:
                _playerInput = PLAYERINPUT::LEFT;
                break;
            case KEY_RIGHT:
            case KEY_KEY_D:
                _playerInput = PLAYERINPUT::RIGHT;
                break;
            default:
                _playerInput = PLAYERINPUT::NONE;
                break;
        }
    }
    return false;
}


