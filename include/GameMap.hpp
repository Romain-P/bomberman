//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMAP_HPP
#define CPP_INDIE_STUDIO_GAMEMAP_HPP

#include <string>

class GameMap
{
public:
    GameMap(std::string &filename);
    GameMap(int level);
    int getMapPosition(int x, int y) const;
private:
    void ParseMap();
    int _completionTime;
    int _map[13][11];
};
#endif //CPP_INDIE_STUDIO_GAMEMAP_HPP
