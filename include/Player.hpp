//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
#define CPP_INDIE_STUDIO_PLAYER_HPP

class Player;

#include <irrlicht.h>
#include <array>
#include <memory>
#include "GameObject.hpp"
#include "PlayerBuff.hpp"

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

class Player : public GameObject
{
public:
    Player(GameManager &manager, int playerNbr, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void setInputs(std::array<bool, 6> inputs) { _inputs = inputs; }
    void Start();
    void Update();
    void LateUpdate();
    void Destroy();
    void GiveBomb();
    void IncreaseBombPower() { _bombPower++; }
    void CheckCollisions();
    bool UseBombBuff();
    void ApplyBuffs();
    void IncreaseScore(int increment) { _score += increment; }
    int getScore() { return _score; }
    std::array<bool, 6> &getInputs() { return _inputs; }
    std::vector<std::unique_ptr<PlayerBuff>> &getBuffs() { return _buffs; }
    int getPlayerNBr() { return _playerNbr; }
    const std::string &getCharacterColor() { return Characters[_playerNbr]; }
    void setSpeed(float speed) { _speed = speed; }
    float getSpeed() { return _speed; }
    static const std::array<std::string, 4> Characters;
protected:
    void PlayAnimation(PLAYERANIM anim);
    void UpdatePosition();
    void PlaceBomb();
    bool IsValidPosition(vector2df position);
    std::array<bool, 6> _inputs;
    float _speed;
    const float BaseSpeed = 2.0f;
    vector2df GetMovement();
    int _bombCount;
    bool _canPlaceBomb;
    PLAYERANIM _anim;
    irr::scene::IAnimatedMeshSceneNode *_node;
    int _playerNbr;
    int _score;
    int _bombPower;
    static constexpr int BaseBombPower = 3;
    std::vector<std::unique_ptr<PlayerBuff>> _buffs;
};

class MainPlayer : public Player
{
public:
    MainPlayer(GameManager &manager, int playerNbr = 0, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
};
#endif //CPP_INDIE_STUDIO_PLAYER_HPP
