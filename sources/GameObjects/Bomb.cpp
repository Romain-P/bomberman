//
// Created by Mardel on 31/05/18.
//

#include <iostream>
#include <Explosion.hpp>
#include "GameManager.hpp"
#include "BomberWave.hpp"
#include "Bomb.hpp"

Bomb::Bomb(int power, Player &player, GameManager &manager, vector2df position, vector2df rotation) :
        GameObject(manager, position, rotation), _player(player), _power(power), _countDown(_explosionTime)
{
    Start();
}

void Bomb::Start()
{
    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IMesh *mesh = device->getSceneManager()->getMesh("resources/models/Bomb/Bomb.obj");

    _node = device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture("resources/models/Bomb/Bomb.png"));
    _node->setPosition(GameMap::mapToEngine(_position));
}

void Bomb::Update()
{
    _countDown -= _manager.getDeltaTime();
    if (_countDown <= 0)
        Explode();
}

void Bomb::Explode()
{
    _player.GiveBomb();
    _manager.SpawnObject(new Explosion(_manager, vector2df(_position.X, _position.Y)));
    ExplodeLine(1, 0);
    ExplodeLine(0, 1);
    ExplodeLine(-1, 0);
    ExplodeLine(0, -1);
    Destroy();
}

void Bomb::ExplodeLine(int x, int y)
{
    int i = 1;
    while (i <= _power)
    {
        if (_position.X + x * i < 0 || _position.Y + y * i >= 12
            || _position.Y + y * i < 0 || _position.X + x * i >= 12)
            return;
        auto collisions = _manager.getObjectsAtPosition(vector2df(_position.X + x * i, _position.Y + y * i));
        for (auto it = collisions.begin(); it != collisions.end();)
        {
            auto tags = (*it)->getTags();
            for (auto itTags = tags.begin(); itTags != tags.end(); itTags++)
            {
                if (*itTags == GOTAG::DESTROYABLE)
                {
                    _manager.SpawnObject(new Explosion(_manager, vector2df(_position.X + x * i, _position.Y + y * i)));
                    (*it)->Destroy();
                }
            }
            return;
        }
        _manager.SpawnObject(new Explosion(_manager, vector2df(_position.X + x * i, _position.Y + y * i)));
        i++;
    }
}

void Bomb::Destroy()
{
    _node->remove();
    GameObject::Destroy();
}