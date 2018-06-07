//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMAP_HPP
#define CPP_INDIE_STUDIO_GAMEMAP_HPP

#include <string>
#include <irrlicht.h>

class GameMap
{
public:
    GameMap();
    int getMapPosition(int x, int y) const;
    static irr::core::vector3df mapToEngine(irr::core::vector2df &pos);
    static irr::core::vector2df engineToMap(irr::core::vector3df &pos);
    static const int MapSize = 12;
protected:
    int _map[12][12];
};

class SoloMap : public GameMap
{
public:
    SoloMap(std::string &filename);
    SoloMap(int level);
    int getCompletionTime() { return _completionTime; }
    int getEnemyCount() { return _enemyCount; }
private:
    int _level;
    std::string _fileName;
    void ParseMap();
    int _completionTime;
    int _enemyCount;
};
#endif //CPP_INDIE_STUDIO_GAMEMAP_HPP
