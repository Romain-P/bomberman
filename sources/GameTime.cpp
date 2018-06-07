//
// Created by Mardel on 30/05/18.
//

#include "GameTime.hpp"

GameTime::GameTime(irr::IrrlichtDevice *device) : _device(device)
{
    _previousTime = _device->getTimer()->getTime();
}

void GameTime::Update()
{
    float currTime = _device->getTimer()->getTime();
    _deltaTime = (currTime - _previousTime) / 1000.0f;
    _previousTime = currTime;
}

void GameTime::Reset()
{
    _previousTime = _device->getTimer()->getTime();
    _deltaTime = 0;
}
