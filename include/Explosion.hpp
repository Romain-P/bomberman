//
// Created by Mardel on 07/06/18.
//

#ifndef CPP_INDIE_STUDIO_EXPLOSION_HPP
#define CPP_INDIE_STUDIO_EXPLOSION_HPP

#include "GameObject.hpp"


class Explosion : public GameObject
{
public:
    Explosion(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Start();
    void Update();
    void Destroy();
private:
    float _countDown;
    static constexpr float LifeTime = 0.5f;
    irr::scene::IParticleSystemSceneNode *_node;
};

#endif //CPP_INDIE_STUDIO_EXPLOSION_HPP
