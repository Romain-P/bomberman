//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMAP_HPP
#define CPP_INDIE_STUDIO_GAMEMAP_HPP

#include <string>
#include <irrlicht.h>
#include <vector>
#include <tuple>
#include <unordered_map>
#include "Serializable.h"

using pos_x = size_t;
using pos_y = size_t;
using spawn_type = int;
using positions_t = std::vector<std::tuple<pos_x, pos_y>>;

class GameMap: public Serializable {
public:
    static constexpr size_t WIDTH = 12;
    static constexpr size_t HEIGHT = 12;

    enum CellType {
        NONE = 0,
        WALL,
        BREAKABLE_WALL,
        ENEMY_SPAWN,
        PLAYER_SPAWN
    };
    GameMap();
    GameMap(int data[HEIGHT][WIDTH], size_t completionTime, ssize_t enemies = -1);
    void serialize(BinaryDataWriter &writer) const final;
    void deserialize(BinaryDataReader &reader) final;
    void set(int x, int y, int value);
    bool isWalkable(pos_x x, pos_y y) const;
    positions_t const &getEnemySpawns() const;
    positions_t const &getPlayerSpawns() const;
    int getMapPosition(int x, int y) const;
    size_t getCompletionTime() const { return _completionTime; }
    int getEnemyCount() const { return _enemies; }
    irr::core::vector2df getGoal() { return _goal; }

    int (&getData())[HEIGHT][WIDTH];

    static irr::core::vector3df mapToEngine(irr::core::vector2df &pos);
    static irr::core::vector2df engineToMap(irr::core::vector3df &pos);
    static const int MapSize = 12;
protected:
    int _map[HEIGHT][WIDTH];
private:
    irr::core::vector2df _spawn;
    irr::core::vector2df _goal;
    size_t _completionTime;
    ssize_t _enemies;
    std::unordered_map<spawn_type, positions_t> _spawns;
};
#endif //CPP_INDIE_STUDIO_GAMEMAP_HPP
