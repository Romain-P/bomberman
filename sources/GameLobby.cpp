//
// Created by Mardel on 10/06/18.
//

#include <Player.hpp>
#include "GameLobby.hpp"

/*
GameLobby::GameLobby(irr::IrrlichtDevice * const device, bool host) : _playerCount(0), _device(device), _host(host)
{
}

void GameLobby::DrawLobby()
{
    _camera = _device->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(-50, 40, 0));
    _camera->setTarget(irr::core::vector3df(0, 40, 0));

    _device->getSceneManager()->addLightSceneNode(0, irr::core::vector3df(0, 20, 0), irr::video::SColorf(1, 1, 1));
    _device->getSceneManager()->setAmbientLight(irr::video::SColor(0, 160, 160, 160));

    irr::scene::IMesh *mesh = _device->getSceneManager()->getMesh("resources/models/Pillar.obj");
    irr::scene::IMeshSceneNode *node = _device->getSceneManager()->addMeshSceneNode(mesh);
    node->setPosition(irr::core::vector3df(-80, 20, 0));
    node->setMaterialTexture(0, _device->getVideoDriver()->getTexture("resources/models/Pillar/Pillar.jpg"));
    mesh = _device->getSceneManager()->getMesh("resources/models/Pillar.obj");
    node = _device->getSceneManager()->addMeshSceneNode(mesh);
    node->setPosition(irr::core::vector3df(0, 20, 0));
    node->setMaterialTexture(0, _device->getVideoDriver()->getTexture("resources/models/Pillar/Pillar.jpg"));
    mesh = _device->getSceneManager()->getMesh("resources/models/Pillar.obj");
    node = _device->getSceneManager()->addMeshSceneNode(mesh);
    node->setMaterialTexture(0, _device->getVideoDriver()->getTexture("resources/models/Pillar/Pillar.jpg"));
    node->setPosition(irr::core::vector3df(80, 20, 0));
}

void GameLobby::AddPlayer()
{
    irr::scene::IAnimatedMesh *mesh = _device->getSceneManager()->getMesh("resources/models/Character/Bomberman.MD3");
    irr::scene::IAnimatedMeshSceneNode *node = _device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
    node->setPosition(irr::core::vector3df(-80 + (80 * _playerCount), 40, 0));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setScale(irr::core::vector3df(6, 6, 6));
    node->setRotation(irr::core::vector3df(0, 0, 0));
    node->setAnimationSpeed(30);
    node->setLoopMode(true);
    node->setMaterialTexture(0, _device->getVideoDriver()->getTexture(("resources/models/Character/" + Player::Characters[_playerCount] + "BombermanTextures.png").c_str()));
    node->setFrameLoop(27, 76);
    _playerCount++;
    _playerNodes.insert(std::pair<int, irr::scene::IAnimatedMeshSceneNode>(_playerCount, node));
}*/
