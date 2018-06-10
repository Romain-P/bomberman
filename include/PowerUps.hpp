//
// Created by Mardel on 09/06/18.
//

#ifndef CPP_INDIE_STUDIO_POWERUPS_HPP
#define CPP_INDIE_STUDIO_POWERUPS_HPP

class PowerUp;

#include "GameObject.hpp"
#include "PlayerBuff.hpp"

class PowerUp : public GameObject
{
public:
    PowerUp(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    virtual PlayerBuff *GiveBuff(Player &player) = 0;
    virtual void Start() = 0;
    void Update();
    void Destroy();
protected:
    static constexpr float RotationSpeed = 30.0f;
    irr::scene::IMeshSceneNode *_node;
};

class SpeedPowerUp : public PowerUp
{
public:
    SpeedPowerUp(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    PlayerBuff *GiveBuff(Player &player) { return new SpeedBuff(player);}
    void Start();
};

class BonusBombPowerUp : public PowerUp
{
public:
    BonusBombPowerUp(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    PlayerBuff *GiveBuff(Player &player) { return new BonusBombBuff(player); }
    void Start();
};

class BombPowerPowerUp : public PowerUp
{
public:
    BombPowerPowerUp(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    PlayerBuff *GiveBuff(Player &player) { return new BombPowerBuff(player); }
    void Start();
};

#endif //CPP_INDIE_STUDIO_POWERUPS_HPP
