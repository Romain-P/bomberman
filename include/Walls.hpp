//
// Created by Mardel on 06/06/18.
//

#ifndef CPP_INDIE_STUDIO_WALLS_HPP
#define CPP_INDIE_STUDIO_WALLS_HPP

#include <IMeshSceneNode.h>
#include <IrrlichtDevice.h>
#include "GameObject.hpp"

class Wall : public GameObject
{
public:
    Wall(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Start();
    void Destroy();
private:
    irr::scene::IMeshSceneNode *_node;
};

class DestroyableWall : public GameObject
{
public:
    DestroyableWall(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Start();
    void Destroy();
private:
    irr::scene::IMeshSceneNode *_node;
};
#endif //CPP_INDIE_STUDIO_WALLS_HPP
