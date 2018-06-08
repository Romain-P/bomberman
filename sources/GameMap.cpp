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

constexpr size_t GameMap::WIDTH;
constexpr size_t GameMap::HEIGHT;

void GameMap::set(int x, int y, int value) {
    _map[y][x] = value;
}

GameMap::GameMap(int (*data)[WIDTH], size_t completionTime, ssize_t enemies) {
    _completionTime = completionTime;
    _enemies = enemies;

    for (pos_y y = 0; y < HEIGHT; ++y) {
        for (pos_x x = 0; x < WIDTH; ++x) {
            int &cell_type = data[y][x];
            _map[y][x] = cell_type;

            if (cell_type == PLAYER_SPAWN)
            {
                _spawn = vector2df(x, y);
            }
            else if (cell_type == ENEMY_SPAWN)
                _goal = vector2df(x, y);
        }
    }
}

bool GameMap::isWalkable(pos_x x, pos_y y) const {
    int celltype = _map[y][x];

    return celltype == NONE || celltype == PLAYER_SPAWN;
}

void GameMap::serialize(BinaryDataWriter &writer) const {
    writer.writeUint(_completionTime);
    writer.writeInt(static_cast<int32_t>(_enemies));
    writer.writeUint(HEIGHT * WIDTH);

    for (const auto &y : _map)
        for (int x : y)
            writer.writeInt(x);
}

void GameMap::deserialize(BinaryDataReader &reader) {
    _completionTime = reader.readUint();
    _enemies = reader.readInt();
    size_t map_size = reader.readUint();

    if (map_size != HEIGHT * WIDTH)
        throw std::runtime_error("invalid map size loaded");

    for (pos_y y = 0; y < HEIGHT; ++y) {
        for (pos_x x = 0; x < WIDTH; ++x) {
            int &cell = _map[y][x];
            cell = reader.readInt();

            if (cell == PLAYER_SPAWN)
            {
                _spawn = vector2df(x, y);
            }
            else if (cell == ENEMY_SPAWN)
                _goal = vector2df(x, y);
        }
    }
}

positions_t const &GameMap::getPlayerSpawns() const {
    return _spawns.at(PLAYER_SPAWN);
}

positions_t const &GameMap::getEnemySpawns() const {
    return _spawns.at(ENEMY_SPAWN);
}

/*int **GameMap::getData() const {
    return _map;
}*/
