//
// Created by Mardel on 09/06/18.
//

#ifndef CPP_INDIE_STUDIO_BACKGROUNDLOADER_HPP
#define CPP_INDIE_STUDIO_BACKGROUNDLOADER_HPP

#include <irrlicht.h>
#include <string>
#include <array>

using namespace irr;
using namespace core;

class BackgroundLoader
{
public:
    BackgroundLoader(irr::IrrlichtDevice *device);
    void LoadTerrain(std::string &path);
    void LoadBackground(std::string &path);
    void LoadRandomTerrain();
    void LoadRandomBackground();
private:
    irr::IrrlichtDevice *_device;
    static const std::array<std::string, 7> Skyboxes;
    static const std::array<std::string, 3> Terrains;
    irr::scene::IMeshSceneNode *_terrain;
    irr::video::ITexture *_terrainTexture;
    irr::scene::IMeshSceneNode *_background;
};

#endif //CPP_INDIE_STUDIO_BACKGROUNDLOADER_HPP
