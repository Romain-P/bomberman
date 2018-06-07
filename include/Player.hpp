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
    Player(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    const std::array<bool, 6> &getInput() { return _inputs; }
    virtual void Start();
    void Update();
    void LateUpdate();
    void GiveBomb();
protected:
    bool _canPlaceBomb;
    quaternion LookRotation(vector3df forward);
    virtual void PlayAnimation(PLAYERANIM anim) = 0;
    virtual void UpdatePosition() = 0;
    virtual void UpdateRotation(vector2df oldpos, vector2df newpos) = 0;
    virtual void PlaceBomb() = 0;
    bool IsValidPosition(vector2df position);
    std::array<bool, 6> _inputs;
    const float _speed = 2.0f;
    vector2df GetMovement();
    int _bombCount;
    PLAYERANIM _anim;
};

class SoloPlayer : public Player
{
public:
    SoloPlayer(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Start();
private:
    void PlaceBomb();
    void PlayAnimation(PLAYERANIM anim);
    void UpdateRotation(vector2df oldpos, vector2df newpos);
    void UpdatePosition();
    PlayerEventReceiver _inputReceiver;
    irr::scene::IAnimatedMeshSceneNode *_node;
};
#endif //CPP_INDIE_STUDIO_PLAYER_HPP
