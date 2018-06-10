//
// Created by Mardel on 31/05/18.
//

#include <GameUtils.hpp>
#include "Monster.hpp"

const std::array<vector2df, 4> Monster::Directions = {vector2df(1, 0), vector2df(-1, 0), vector2df(0, 1), vector2df(0, -1) };

Monster::Monster(GameManager &manager, vector2df position, vector2df rotation) :
        GameObject(manager, position, rotation)
{
    _tags.push_back(GOTAG::DEATH);
    _tags.push_back(GOTAG::DESTROYABLE);
    Start();
}

void Monster::Destroy()
{
    _manager.IncreaseScore(100);
    _node->remove();
    GameObject::Destroy();
}

void Monster::Start()
{
    irr::IrrlichtDevice *device = _manager.getDevice();
    irr::scene::IMesh *mesh = device->getSceneManager()->getMesh("resources/models/Jesus/Jesus.obj");

    _node = device->getSceneManager()->addMeshSceneNode(mesh);
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMaterialTexture(0, device->getVideoDriver()->getTexture("resources/models/Jesus/Jesus.png"));
    _position = vector2df(_position.X + 0.5f, _position.Y + 0.5f);
    _node->setPosition(GameMap::mapToEngine(_position));
    _node->setScale(vector3df(0.4f, 0.4f, 0.4f));
    ChangeDirection();
}

void Monster::Update()
{
    vector2df newPosition = _position + (_direction * Speed * _manager.getDeltaTime());
    if (IsValidPosition(newPosition))
    {
        _node->setRotation((GetRotationFromTo(GameMap::mapToEngine(_position), GameMap::mapToEngine(newPosition))));
        _position = newPosition;
        _node->setPosition(GameMap::mapToEngine(_position));
    }
    else
        ChangeDirection();
    CheckCollisions();
}

void Monster::CheckCollisions()
{
    std::vector<GOTAG> deathTag(1, GOTAG::DESTROY);

    if (!_manager.getCollisionsWithTags(*this, deathTag).empty())
    {
        Destroy();
        return;
    }
}

bool Monster::IsValidPosition(vector2df position)
{
    auto collisions = _manager.getObjectsAtPosition(position);

    if (position.X < 0 || position.Y >= 12 || position.Y < 0 || position.X >= 12)
        return false;
    for (auto it = collisions.begin(); it != collisions.end(); it++)
    {
        auto tags = (*it)->getTags();
        for (auto itTags = tags.begin(); itTags != tags.end(); itTags++)
        {
            if (*itTags == GOTAG::SOLID)
                return false;
        }
    }
    return true;
}

void Monster::ChangeDirection()
{
    vector2df direction;

    do
    {
        direction = Directions[rand() % 4];
    }
    while (!IsValidPosition(_position + direction));
    _direction = direction;
}

