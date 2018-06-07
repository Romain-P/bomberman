//
// Created by Mardel on 28/05/18.
//

#include "GameRenderer.hpp"
#include "GameObject.hpp"


GameRenderer::GameRenderer(irr::IrrlichtDevice *const device) : _device(device)
{
    PlaceCamera();
    PlaceLights();
    CreateTerrain();
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

void GameRenderer::CreateTerrain()
{
    _terrain = _device->getSceneManager()->addCubeSceneNode(12, nullptr, 1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(10, 10, 10));
    _terrainTexture = _device->getVideoDriver()->getTexture("resources/textures/Terrain/terrain1.jpg");
    _terrain->setMaterialTexture(0, _terrainTexture);
    _terrain->setMaterialFlag(irr::video::EMF_LIGHTING, true);

    irr::scene::IMesh *mesh = _device->getSceneManager()->getGeometryCreator()->createPlaneMesh(core::dimension2d<f32>(800, 600));
    _background = _device->getSceneManager()->addMeshSceneNode(mesh);
    _background->setScale((vector3df(1)));
    _background->setMaterialTexture(0, _device->getVideoDriver()->getTexture("resources/textures/Skybox/skybox1.jpg"));
    _background->setPosition(irr::core::vector3df(20,-115,0));
    _background->setRotation(vector3df(0, 90, 45));
}

void GameRenderer::Render()
{
    _device->getVideoDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
    _device->getSceneManager()->drawAll();
    _device->getGUIEnvironment()->drawAll();
    _device->getVideoDriver()->endScene();
}

void GameRenderer::RenderMap(GameMap &map)
{

}

void GameRenderer::RenderObjects(std::vector<GameObject> &objects)
{

}

void GameRenderer::RenderUI()
{

}

void GameRenderer::RenderPlayer(Player &player)
{

}
