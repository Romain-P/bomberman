//
// Created by Mardel on 24/05/18.
//

#include "GameManager.hpp"
#include "GameObject.hpp"
#include <irrlicht.h>

GameObject::GameObject(GameManager &manager, vector2df position, vector2df rotation) : _toBeDestroyed(false), _manager(manager), _position(position), _rotation(rotation)
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

bool GameObject::HasTag(GOTAG tag)
{
    for (auto it = _tags.begin();  it != _tags.end(); it++)
    {
        if (*it == tag)
            return true;
    }
    return false;
}

void GameObject::Destroy()
{
    _toBeDestroyed = true;
}


