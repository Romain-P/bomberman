//
// Created by Mardel on 06/06/18.
//

#include <GameManager.hpp>
#include <iostream>
#include <PowerUps.hpp>
#include "Walls.hpp"

Wall::Wall(GameManager &manager, vector2df position, vector2df rotation) : GameObject(manager, position, rotation)
{
    _tags.push_back(GOTAG::SOLID);
    Start();
}

void Wall::Destroy()
{
    _node->remove();
    GameObject::Destroy();
}

void Wall::Start()
{
    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IMesh *mesh = device->getSceneManager()->getMesh("resources/models/Column/Column.obj");

    _node = device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture("resources/models/Column/Column.png"));
    _position = vector2df(_position.X + 0.5f, _position.Y + 0.5f);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setScale(vector3df(4.2f, 2.5f, 4.2f));
}

DestroyableWall::DestroyableWall(GameManager &manager, vector2df position, vector2df rotation)
        : GameObject(manager, position, rotation)
{
    _tags.push_back(GOTAG::SOLID);
    _tags.push_back(GOTAG::DESTROYABLE);
   Start();
}

void DestroyableWall::Destroy()
{
    SpawnPowerUp();
    _node->remove();
    GameObject::Destroy();
}

void DestroyableWall::SpawnPowerUp()
{
    if (rand() % 5 != 0)
        return;
    int powerUp = rand() % 3;
    switch (powerUp)
    {
        case 0:
            _manager.SpawnObject(new SpeedPowerUp(_manager, _position));
            break;
        case 1:
            _manager.SpawnObject(new BonusBombPowerUp(_manager, _position));
            break;
        case 2:
            _manager.SpawnObject(new BombPowerPowerUp(_manager, _position));
            break;
    }
}

void DestroyableWall::Start()
{

    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IMesh *mesh = device->getSceneManager()->getMesh("resources/models/PalmTree/plamtree.obj");

    _node = device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setRotation(vector3df(0, rand() % 360, 0));
     _node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    _position = vector2df(_position.X + 0.5f, _position.Y + 0.5f);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setScale(vector3df(2.5f + (float)(rand() % 10) / 10, 1.5f + (float)(rand() % 10) / 10, 2.5f + (float)(rand() % 10) / 10));
}

Goal::Goal(GameManager &manager, vector2df position, vector2df rotation) : GameObject(manager, position, rotation)
{
    _tags.push_back(GOTAG::GOAL);
    Start();
}

void Goal::Destroy()
{
    _node->remove();
    GameObject::Destroy();
}

void Goal::Start() {
    GameObject::Start();

    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IMesh *mesh = device->getSceneManager()->getMesh("resources/models/Door/InteriorDoor.obj");

    _node = device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture("resources/models/Door/InteriorDoor_DiffuceBlue.jpg"));
    _node->setRotation(vector3df(0, 90, 0));
    _position = vector2df(_position.X + 0.5f, _position.Y + 0.5f);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setScale(vector3df(0.2f, 0.2f, 0.2f));
}
