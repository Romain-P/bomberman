//
// Created by Mardel on 10/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMELOBBY_HPP
#define CPP_INDIE_STUDIO_GAMELOBBY_HPP

#include <irrlicht.h>
#include <map>

class GameLobby
{
public:
    GameLobby(bool host = false);
    void AddPlayer();
private:
    void Draw(int playercount);
    std::map<int, irr::scene::IAnimatedMeshSceneNode *> _playerNodes;
    bool _host;
    irr::scene::ICameraSceneNode *_camera;
};
#endif //CPP_INDIE_STUDIO_GAMELOBBY_HPP
