//
// Created by Mardel on 30/05/18.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <Walls.hpp>
#include "GameMap.hpp"


GameMap::GameMap()
{
}

int GameMap::getMapPosition(int x, int y) const
{
    return _map[y][x];
}

irr::core::vector3df GameMap::mapToEngine(irr::core::vector2df &pos)
{
    irr::core::vector3df newpos;

    newpos.X = (60 - (pos.Y * 10));
    newpos.Y = 60;
    newpos.Z = (60 - (pos.X * 10));
    return newpos;
}

irr::core::vector2df GameMap::engineToMap(irr::core::vector3df &pos)
{
    irr::core::vector2df newpos;

    newpos.X = ((pos.Z + 60) / 10);
    newpos.Y = ((pos.X + 60) / 10);
    return newpos;
}

SoloMap::SoloMap(std::string &fileName) : GameMap(), _fileName(fileName)
{
    ParseMap();
}

SoloMap::SoloMap(int level) : GameMap()
{
    int lvl = level;

    _fileName = "resources/maps/" + std::to_string(lvl);
    ParseMap();
}

void SoloMap::ParseMap()
{
    std::ifstream file(_fileName);
    int linecount = 0;

    for (std::string line; getline(file, line);)
    {
        if (linecount == 0)
            _completionTime = std::stoi(line);
        else if (linecount == 1)
            _enemyCount = std::stoi(line);
        else
        {
            int y = linecount - 2;
            if (line.size() == 12)
            {
                for (int x = 0; x < (int)line.size(); x++)
                {
                    _map[y][x] = std::stoi(std::to_string(line[x] - 48));
                }
            }
        }
        linecount++;
    }

}

