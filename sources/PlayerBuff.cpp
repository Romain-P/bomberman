//
// Created by Mardel on 09/06/18.
//

#include "PlayerBuff.hpp"

PlayerBuff::PlayerBuff(Player &player, std::string iconPath, float duration, BUFFTYPE type) :  _player(player), _iconPath(iconPath), _countDown(duration), _type(type)
{
}

void PlayerBuff::Apply(float deltaTime)
{
    _countDown -= deltaTime;
    if (_countDown < 0)
        _countDown = 0;
}

SpeedBuff::SpeedBuff(Player &player) : PlayerBuff(player,
                                                  "resources/ui/Buffs/SpeedBuff.png",
                                                  10,
                                                  BUFFTYPE::SPEED)
{
}

void SpeedBuff::Apply(float deltaTime)
{
    _player.setSpeed(_player.getSpeed() * SpeedMultiplier);
    PlayerBuff::Apply(deltaTime);
}

BonusBombBuff::BonusBombBuff(Player &player) : PlayerBuff(player,
                                                          "resources/ui/Buffs/BombIcon.png",
                                                          -1,
                                                          BUFFTYPE::BOMB)
{
}

BombPowerBuff::BombPowerBuff(Player &player) : PlayerBuff(player,
                                                          "resources/ui/Buffs/BombPower.png",
                                                          10,
                                                          BUFFTYPE::BOMBPOWER)
{
}

void BombPowerBuff::Apply(float deltaTime)
{
    _player.IncreaseBombPower();
    PlayerBuff::Apply(deltaTime);
}