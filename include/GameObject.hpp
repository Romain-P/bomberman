//
// Created by Mardel on 24/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEOBJECT_HPP
#define CPP_INDIE_STUDIO_GAMEOBJECT_HPP

class GameManager;

#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace core;

enum class GOTAG
{
    SOLID,
    DESTROYABLE,
    DEATH
};

enum class GOTYPE
{
    PLAYER,
    BOMB,
    WALL,
    DESTROYABLEWALL
};

class GameObject
{
public:
    GameObject(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    GameObject &operator=(const GameObject &obj) { return *this; }
    const std::vector<GOTAG> &getTags() { return _tags; }
    vector2df getPosition() { return _position; }
    vector2df getRotation() { return _rotation; }
    bool shouldBeDestroyed() { return _toBeDestroyed; }
    virtual void Destroy();
    void setPosition(vector2df position) {  _position = position; }
    void setRotation(vector2df rotation) { _rotation = rotation; }
    int getId() { return _id; }
    bool HasTag(GOTAG tag);
protected:
    bool _toBeDestroyed;
    std::vector<GOTAG> _tags;
    GameManager &_manager;
    vector2df _position;
    vector2df _rotation;
    int _id;
};

#endif //CPP_INDIE_STUDIO_GAMEOBJECT_HPP
