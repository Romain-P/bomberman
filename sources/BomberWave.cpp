//
// Created by Mardel on 23/05/18.
//

#include "BomberWave.hpp"
#include <irrlicht.h>
#include <Exceptions.hpp>
#include <GameServer.h>
#include <thread>
#include <GameSessionConnector.h>
#include "GameManager.hpp"

BomberWave::BomberWave() : _mainMenu()
{
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
    Device->getGUIEnvironment()->clear();
    switch(_mainMenu.RunAdventure())
    {
        case MAINMENUCHOICE::SOLO :
            {
            Device->getGUIEnvironment()->clear();
            GameManager gameManager;
            gameManager.LaunchGame();
            }
            break;
        case MAINMENUCHOICE::DUO :
            {
                Device->getGUIEnvironment()->clear();
                GameManager gameManagerDuo(true);
                gameManagerDuo.LaunchGame();
            }
            break;
        case MAINMENUCHOICE::BACK :
            std::cout << "go back" << std::endl;
            Device->getGUIEnvironment()->clear();
            return;
        default:
            break;
    }
}

void BomberWave::LaunchMultiplayerHost()
{
    Device->getGUIEnvironment()->clear();
}

void BomberWave::LaunchMultiplayerJoin()
{
    Device->getGUIEnvironment()->clear();
}

void BomberWave::Launch()
{
    _gameRunning = true;
    LaunchMainMenu();
}
