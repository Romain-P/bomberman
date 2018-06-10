//
// Created by Mardel on 28/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMERENDERER_HPP
#define CPP_INDIE_STUDIO_GAMERENDERER_HPP

#include <vector>
#include "GameObject.hpp"
#include "GameMap.hpp"
#include "Player.hpp"

class GameRenderer
{
public:
    GameRenderer(irr::IrrlichtDevice * const device);
    void Render();
private:
    void PlaceLights();
    void PlaceCamera();
    irr::IrrlichtDevice * const _device;
    irr::scene::ICameraSceneNode *_camera;
};

#endif //CPP_INDIE_STUDIO_GAMERENDERER_HPP
