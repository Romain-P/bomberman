//
// Created by Mardel on 24/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEOBJECT_HPP
#define CPP_INDIE_STUDIO_GAMEOBJECT_HPP

#include <vector3d.h>

using namespace irr;

using namespace core;

class GameObject
{
public:
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    vector3df getPosition() { return _position; }
    vector3df getRotation() { return _rotation; }
    void setPosition(vector3df position) { _position = position; }
    void setRotation(vector3df rotation) {_rotation = rotation; }
private:
    vector3df _position;
    vector3df _rotation;
};

#endif //CPP_INDIE_STUDIO_GAMEOBJECT_HPP
