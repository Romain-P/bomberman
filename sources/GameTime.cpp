//
// Created by Mardel on 30/05/18.
//

#include <BomberWave.hpp>
#include "GameTime.hpp"

GameTime::GameTime()
{
    _previousTime = Device->getTimer()->getTime();
}

void GameTime::Update()
{
    float currTime = Device->getTimer()->getTime();
    _deltaTime = (currTime - _previousTime) / 1000.0f;
    _previousTime = currTime;
}

void GameTime::Reset()
{
    _previousTime = Device->getTimer()->getTime();
    _deltaTime = 0;
}
