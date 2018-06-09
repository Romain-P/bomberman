//
// Created by Mardel on 09/06/18.
//

#ifndef CPP_INDIE_STUDIO_PLAYERBUFF_HPP
#define CPP_INDIE_STUDIO_PLAYERBUFF_HPP

class PlayerBuff;

#include <string>
#include "Player.hpp"

enum class BUFFTYPE
{
    SPEED,
    BOMB,
    BOMBPOWER
};

class PlayerBuff
{
public:
    PlayerBuff(Player &player, std::string iconPath, float duration, BUFFTYPE type);
    virtual void Apply(float deltaTime);
    std::string &getIcon() { return _iconPath; }
    float getCountDown() { return _countDown; }
    BUFFTYPE getType() { return _type; }
protected:
    BUFFTYPE _type;
    float _countDown;
    Player &_player;
    std::string _iconPath;
};

class SpeedBuff : public PlayerBuff
{
public:
    SpeedBuff(Player &player);
    void Apply(float deltaTime);
    static constexpr float SpeedMultiplier = 1.1f;
};

class BonusBombBuff : public PlayerBuff
{
public:
    BonusBombBuff(Player &player);
    void Apply(float deltaTime) {};
};

class BombPowerBuff : public PlayerBuff
{
public:
    BombPowerBuff(Player &player);
    void Apply(float deltaTime);
};
#endif //CPP_INDIE_STUDIO_PLAYERBUFF_HPP
