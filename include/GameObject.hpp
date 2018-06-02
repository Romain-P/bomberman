//
// Created by Mardel on 24/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEOBJECT_HPP
#define CPP_INDIE_STUDIO_GAMEOBJECT_HPP

class GameManager;

#include <vector3d.h>

using namespace irr;
using namespace core;

class GameObject
{
public:
    GameObject(GameManager &manager, vector3df position = vector3df(0,0,0), vector3df rotation = vector3df(0,0,0));
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    vector3df getPosition() { return _position; }
    vector3df getRotation() { return _rotation; }
    void setPosition(vector3df position) {  _position = position; }
    void setRotation(vector3df rotation) { _rotation = rotation; }
    int getId() { return _id; }
protected:
    GameManager &_manager;
    vector3df _position;
    vector3df _rotation;
    int _id;
};

#endif //CPP_INDIE_STUDIO_GAMEOBJECT_HPP
