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
    _deltaTime = _device->getTimer()->getTime() - _previousTime;
    _previousTime += _deltaTime;
}

void GameTime::Reset()
{
    _previousTime = _device->getTimer()->getTime();
    _deltaTime = 0;
}
