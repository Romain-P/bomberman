//
// Created by Mardel on 31/05/18.
//

#include "GameManager.hpp"
#include "BomberWave.hpp"
#include "Bomb.hpp"

Bomb::Bomb(GameManager &manager, vector3df position, vector3df rotation) : GameObject(manager, position, rotation)
{

}

void Bomb::Start()
{
    _countDown = _explosionTime;
}

void Bomb::Update()
{
    _countDown -= _manager.getDeltaTime();
    if (_countDown <= 0)
        Explode();
}

void Bomb::LateUpdate()
{
}

void Bomb::Explode()
{
    _manager.getPlayer().GiveBomb();

}
