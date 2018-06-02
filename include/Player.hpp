//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
#define CPP_INDIE_STUDIO_PLAYER_HPP

#include <irrlicht.h>
#include "GameObject.hpp"

using namespace irr;
using namespace core;

enum class PLAYERINPUT
{
    NONE = 101,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PLACEBOMB,
    PAUSE,
};

class PlayerEventReceiver : public irr::IEventReceiver
{
public:
    PlayerEventReceiver(PLAYERINPUT &playerInput);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    PLAYERINPUT &_playerInput;
};

class Player : public GameObject
{
public:
    Player(GameManager &manager, vector3df position = vector3df(0,0,0), vector3df rotation = vector3df(0,0,0));
    PLAYERINPUT getInput() { return _input; }
    void Start();
    void Update();
    void LateUpdate();
    void GiveBomb();
private:
    void PlaceBomb();
    bool IsValidPosition(vector3df position);
    PLAYERINPUT _input;
    PlayerEventReceiver _inputReceiver;
    static const int _speed = 1;
    vector3df GetMovement();
    int _bombCount;
};

#endif //CPP_INDIE_STUDIO_PLAYER_HPP
