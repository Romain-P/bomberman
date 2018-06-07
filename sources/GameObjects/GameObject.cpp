//
// Created by Mardel on 24/05/18.
//

#include "GameManager.hpp"
#include "GameObject.hpp"
#include <irrlicht.h>

GameObject::GameObject(GameManager &manager, vector2df position, vector2df rotation) : _manager(manager), _position(position), _rotation(rotation), _toBeDestroyed(false)
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

void GameObject::Destroy()
{
    _toBeDestroyed = true;
}


