//
// Created by Mardel on 09/06/18.
//

#include <GameMap.hpp>
#include <BomberWave.hpp>
#include "PowerUps.hpp"
#include "GameManager.hpp"

PowerUp::PowerUp(GameManager &manager, vector2df position, vector2df rotation) : GameObject(manager, position, rotation), _node(nullptr)
{
    _tags.push_back(GOTAG::POWERUP);
}

void PowerUp::Destroy()
{
    _node->remove();
    GameObject::Destroy();
}

void PowerUp::Update()
{
    if (!_toBeDestroyed)
    {
        float newY = _node->getRotation().Y + RotationSpeed * _manager.getDeltaTime();
        if (newY > 360)
            newY -= 360;
        _node->setRotation(vector3df(_node->getRotation().X, newY, _node->getRotation().Z));
    }
}

SpeedPowerUp::SpeedPowerUp(GameManager &manager, vector2df position, vector2df rotation) : PowerUp(manager, position, rotation)
{
    Start();
}

void SpeedPowerUp::Start()
{
    irr::scene::IMesh *mesh = Device->getSceneManager()->getMesh("resources/models/PowerUps/SpeedPowerUp/SpeedUp.obj");

    _node = Device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setRotation(vector3df(0, 45, 0));
    _node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("resources/models/PowerUps/SpeedPowerUp/AU_Display_MAT_Base_Color.png"));
    _node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setPosition(vector3df(_node->getPosition().X, _node->getPosition().Y + 5, _node->getPosition().Z));
    _node->setScale(vector3df(2, 2, 2));
}

BonusBombPowerUp::BonusBombPowerUp(GameManager &manager, vector2df position, vector2df rotation) : PowerUp(manager, position, rotation)
{
    Start();
}

void BonusBombPowerUp::Start()
{
    irr::scene::IMesh *mesh = Device->getSceneManager()->getMesh("resources/models/Bomb/Bomb.obj");

    _node = Device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setRotation(vector3df(0, 45, 0));
    _node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("resources/models/Bomb/Bomb.png"));
    _node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setPosition(vector3df(_node->getPosition().X, _node->getPosition().Y + 5, _node->getPosition().Z));
    _node->setScale(vector3df(1, 1, 1));
}

BombPowerPowerUp::BombPowerPowerUp(GameManager &manager, vector2df position, vector2df rotation) : PowerUp(manager, position, rotation)
{
    Start();
}

void BombPowerPowerUp::Start()
{
    irr::scene::IMesh *mesh = Device->getSceneManager()->getMesh("resources/models/PowerUps/BombPowerPowerUp/BombPower.obj");

    _node = Device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setRotation(vector3df(0, 45, 0));
    _node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("resources/models/PowerUps/BombPowerPowerUp/SU_Display_MAT_Emissive.png"));
    _node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setPosition(vector3df(_node->getPosition().X, _node->getPosition().Y + 5, _node->getPosition().Z));
    _node->setScale(vector3df(2, 2, 2));
}
