//
// Created by Mardel on 31/05/18.
//

#ifndef CPP_INDIE_STUDIO_BOMB_HPP
#define CPP_INDIE_STUDIO_BOMB_HPP

#include "GameObject.hpp"

class Bomb : public GameObject
{
public:
    Bomb(GameManager &manager, vector3df position = vector3df(0,0,0), vector3df rotation = vector3df(0,0,0));
    void Start();
    void Update();
    void LateUpdate();
private:
    void Explode();
    float _countDown;
    static const float _explosionTime = 3;
};

#endif //CPP_INDIE_STUDIO_BOMB_HPP
