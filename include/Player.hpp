//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
#define CPP_INDIE_STUDIO_PLAYER_HPP

class Player;

#include <irrlicht.h>
#include <array>
#include "GameObject.hpp"

using namespace irr;
using namespace core;

enum class PLAYERINPUT
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    PLACEBOMB,
    PAUSE
};

enum class PLAYERANIM
{
    IDLE,
    WALK
};

class PlayerEventReceiver : public irr::IEventReceiver
{
public:
    PlayerEventReceiver(std::array<bool, 6> &inputs);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    std::array<bool, 6> &_inputs;
};

class Player : public GameObject
{
public:
    Player(GameManager &manager, int playerNbr, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    const std::array<bool, 6> &getInput() { return _inputs; }
    void setInputs(std::array<bool, 6> inputs) { _inputs = inputs; }
    void Start();
    void Update();
    void LateUpdate();
    void GiveBomb();
    int getPlayerNBr() { return _playerNbr; }
protected:
    static const std::array<std::string, 4> Characters;
    void PlayAnimation(PLAYERANIM anim);
    void UpdatePosition();
    void PlaceBomb();
    bool IsValidPosition(vector2df position);
    std::array<bool, 6> _inputs;
    const float _speed = 2.0f;
    vector2df GetMovement();
    int _bombCount;
    bool _canPlaceBomb;
    PLAYERANIM _anim;
    irr::scene::IAnimatedMeshSceneNode *_node;
    int _playerNbr;
};

class MainPlayer : public Player
{
public:
    MainPlayer(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
private:
    PlayerEventReceiver _inputReceiver;
};
#endif //CPP_INDIE_STUDIO_PLAYER_HPP
