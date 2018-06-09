//
// Created by Mardel on 28/05/18.
//

#include "GameRenderer.hpp"
#include "GameObject.hpp"


GameRenderer::GameRenderer(irr::IrrlichtDevice *const device) : _device(device)
{
    PlaceCamera();
    PlaceLights();
}

void GameRenderer::PlaceCamera()
{
    _camera = _device->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(-70, 130, 0));
    _camera->setTarget(irr::core::vector3df(0, 40, 0));
}

void GameRenderer::PlaceLights()
{
    _device->getSceneManager()->addLightSceneNode(0, core::vector3df(0, 20, 0), irr::video::SColorf(1, 1, 1));
    _device->getSceneManager()->setAmbientLight(irr::video::SColor(0, 160, 160, 160));
}

void GameRenderer::Render()
{
    _device->getVideoDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
    _device->getSceneManager()->drawAll();
    _device->getGUIEnvironment()->drawAll();
    _device->getVideoDriver()->endScene();
}