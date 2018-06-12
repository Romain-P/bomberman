//
// Created by Mardel on 07/06/18.
//

#include <GameManager.hpp>
#include <BomberWave.hpp>
#include "Explosion.hpp"

Explosion::Explosion(GameManager &manager, vector2df position, vector2df rotation) : GameObject(manager, position, rotation), _countDown(LifeTime)
{
    _tags.push_back(GOTAG::DESTROY);
    Start();
}

void Explosion::Update()
{
    _countDown -= _manager.getDeltaTime();
    if (_countDown <= 0)
        Destroy();
}

void Explosion::Destroy()
{
    _node->remove();
    GameObject::Destroy();
}

void Explosion::Start()
{
    _node = Device->getSceneManager()->addParticleSystemSceneNode(false);
    _node->setPosition(GameMap::mapToEngine(_position));
    scene::IParticleEmitter *em = _node->createBoxEmitter(
            core::aabbox3d<f32>(-2.5, -0.5f, -2.5f, -0.5f, 2.5f, 2.5f), // emitter size
            core::vector3df(0.0f, 0.0005f, 0.0f),   // initial direction
            1000, 1000,                             // emit rate
            video::SColor(0, 255, 255, 255),       // darkest color
            video::SColor(0, 255, 255, 255),       // brightest color
            800, 2000, 0,                         // min and max age, angle
            core::dimension2df(0.4f, 0.4f),         // min size
            core::dimension2df(0.6f, 0.6f));        // max size

    _node->setEmitter(em);
    em->drop();
    scene::IParticleAffector *paf = _node->createFadeOutParticleAffector();
    _node->addAffector(paf);
    paf->drop();
    _node->setScale(core::vector3df(2, 2, 2));
    _node->setMaterialFlag(video::EMF_LIGHTING, false);
    _node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    video::ITexture *fireTexture = Device->getVideoDriver()->getTexture("resources/textures/Particles/fire.bmp");
    _node->setMaterialTexture(0, fireTexture);
    _node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}
