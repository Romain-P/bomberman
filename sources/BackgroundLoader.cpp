//
// Created by Mardel on 09/06/18.
//

#include <iostream>
#include "BackgroundLoader.hpp"
#include "BomberWave.hpp"


const std::array<std::string, 3> BackgroundLoader::Terrains = {
        "resources/textures/terrains/terrain1.jpg",
        "resources/textures/terrains/terrain2.jpg",
        "resources/textures/terrains/terrain3.jpg",
};

const std::array<std::string, 7> BackgroundLoader::Skyboxes = {
        "resources/textures/skyboxes/skybox1.jpg",
        "resources/textures/skyboxes/skybox2.jpg",
        "resources/textures/skyboxes/skybox3.jpg",
        "resources/textures/skyboxes/skybox4.jpg",
        "resources/textures/skyboxes/skybox5.jpg",
        "resources/textures/skyboxes/skybox6.jpg",
        "resources/textures/skyboxes/skybox7.jpg",
};

BackgroundLoader::BackgroundLoader() :
{

}

void BackgroundLoader::LoadRandomBackground()
{
    std::string bgPath = Skyboxes[rand() % Skyboxes.size()];

    LoadBackground(bgPath);
}

void BackgroundLoader::LoadRandomTerrain()
{
    std::string tPath = Terrains[rand() % Terrains.size()];

    LoadTerrain(tPath);
}

void BackgroundLoader::LoadBackground(std::string &path)
{
    irr::scene::IMesh *mesh = Device->getSceneManager()->getGeometryCreator()->createPlaneMesh(core::dimension2d<f32>(800, 600));
    _background = Device->getSceneManager()->addMeshSceneNode(mesh);
    _background->setScale((vector3df(1)));
    _background->setMaterialTexture(0, Device->getVideoDriver()->getTexture(path.c_str()));
    _background->setPosition(irr::core::vector3df(20,-115,0));
    _background->setRotation(vector3df(0, 90, 45));
}

void BackgroundLoader::LoadTerrain(std::string &path)
{
    _terrain = Device->getSceneManager()->addCubeSceneNode(12, nullptr, 1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(10, 10, 10));
    _terrainTexture = Device->getVideoDriver()->getTexture(path.c_str());
    _terrain->setMaterialTexture(0, _terrainTexture);
    _terrain->setMaterialFlag(irr::video::EMF_LIGHTING, true);
}
