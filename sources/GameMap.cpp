//
// Created by Mardel on 30/05/18.
//

#include "GameMap.hpp"

GameMap::GameMap(std::string &filename)
{

}

GameMap::GameMap(int level)
{

}

void GameMap::ParseMap()
{

}

int GameMap::getMapPosition(int x, int y) const
{
    return _map[y][x];
}
