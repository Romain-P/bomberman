//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMETIME_HPP
#define CPP_INDIE_STUDIO_GAMETIME_HPP

#include <irrlicht.h>

class GameTime
{
public:
    GameTime();
    void Update();
    void Reset();
    float getDeltaTime() { return _deltaTime; }
private:
    float _deltaTime;
    float _previousTime;
};

#endif //CPP_INDIE_STUDIO_GAMETIME_HPP
