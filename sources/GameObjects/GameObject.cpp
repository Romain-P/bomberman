//
// Created by Mardel on 24/05/18.
//

#include "GameManager.hpp"
#include "GameObject.hpp"
#include <irrlicht.h>

GameObject::GameObject(GameManager &manager, vector3df position, vector3df rotation) : _manager(manager), _position(position), _rotation(rotation)
{
    _id = _manager.GenerateId();
}

void GameObject::Start()
{

}

void GameObject::Update()
{
}

void GameObject::LateUpdate()
{

}


