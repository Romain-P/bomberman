//
// Created by Mardel on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMAP_HPP
#define CPP_INDIE_STUDIO_GAMEMAP_HPP

#include <string>
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

    explicit GameMap(int level) {} //TODO ?

    GameMap(int data[HEIGHT][WIDTH], size_t completionTime, ssize_t enemies = -1);

    void serialize(BinaryDataWriter &writer) const final;
    void deserialize(BinaryDataReader &reader) final;

    int getMapPosition(int x, int y) const;
    void set(int x, int y, int value);
    bool isWalkable(pos_x x, pos_y y) const;
    positions_t const &getEnemySpawns() const;
    positions_t const &getPlayerSpawns() const;

private:

    size_t _completionTime;
    ssize_t _enemies;
    int _map[HEIGHT][WIDTH];
    std::unordered_map<spawn_type, positions_t> _spawns;
};

#endif //CPP_INDIE_STUDIO_GAMEMAP_HPP
