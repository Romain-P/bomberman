//
// Created by Mardel on 06/06/18.
//

#include <GameManager.hpp>
#include <iostream>
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
    _node->remove();
    GameObject::Destroy();
}

void DestroyableWall::Start()
{

    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IMesh *mesh = device->getSceneManager()->getMesh("resources/models/PalmTree/source/plamtree/plamtree.obj");

    _node = device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setRotation(vector3df(0, 45, 0));
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture("resources/models/PalmTree/textures/bark.jpg"));
    _node->setMaterialTexture(1, device->getVideoDriver()->getTexture("resources/models/PalmTree/textures/long_leaf_tex.png"));
    _node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    _position = vector2df(_position.X + 0.5f, _position.Y + 0.5f);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setScale(vector3df(2, 1, 2));
}
