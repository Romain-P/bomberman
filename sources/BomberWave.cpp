//
// Created by Mardel on 23/05/18.
//

#include "BomberWave.hpp"
#include <irrlicht.h>
#include <driverChoice.h>
#include <Exceptions.hpp>
#include "GameManager.hpp"

BomberWave::BomberWave() : _device(InitDevice()), _mainMenu(_device)
{
}

irr::IrrlichtDevice *BomberWave::InitDevice()
{
    irr::IrrlichtDevice *device;
    irr::video::E_DRIVER_TYPE driverType = irr::driverChoiceConsole();
    if (driverType == irr::video::EDT_COUNT)
        throw(InitialisationException("Error : Driver could not be loaded"));
    device = irr::createDevice(driverType,
                                irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, nullptr);
    if (device == nullptr)
        throw(InitialisationException("Error : Device creation failed"));
    device->setWindowCaption(L"BomberWave");
    return device;
}

void BomberWave::LaunchMainMenu()
{
    while (_gameRunning)
    {
        switch(_mainMenu.Run())
        {
            case MAINMENUCHOICE::SOLO :
                LaunchSolo();
                break;
            case MAINMENUCHOICE::HOSTMULTIPLAYER :
                LaunchMultiplayerHost();
                break;
            case MAINMENUCHOICE::JOINMULTIPLAYER :
                LaunchMultiplayerJoin();
                break;
            case MAINMENUCHOICE::QUIT :
                _gameRunning = false;
                break;
            default:
                break;
        }
    }
}

void BomberWave::LaunchSolo()
{
    GameManager gameManager(1, _device);

    gameManager.LaunchGame();
}

void BomberWave::LaunchMultiplayerHost()
{

}

void BomberWave::LaunchMultiplayerJoin()
{

}

void BomberWave::Launch()
{
    _gameRunning = true;
    LaunchMainMenu();
}