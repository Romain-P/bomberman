//
// Created by Mardel on 28/05/18.
//

#include "GameRenderer.hpp"
#include "GameObject.hpp"
#include "BomberWave.hpp"

GameRenderer::GameRenderer()
{
    PlaceCamera();
    PlaceLights();
}

void GameRenderer::PlaceCamera()
{
    _camera = Device->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(-70, 130, 0));
    _camera->setTarget(irr::core::vector3df(0, 40, 0));
}

void GameRenderer::PlaceLights()
{
    Device->getSceneManager()->addLightSceneNode(0, core::vector3df(0, 20, 0), irr::video::SColorf(1, 1, 1));
    Device->getSceneManager()->setAmbientLight(irr::video::SColor(0, 160, 160, 160));
}

void GameRenderer::Render()
{
    Device->getVideoDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
    Device->getSceneManager()->drawAll();
    Device->getGUIEnvironment()->drawAll();
    Device->getVideoDriver()->endScene();
}