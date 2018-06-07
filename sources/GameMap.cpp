//
// Created by Mardel on 30/05/18.
//

#include "GameMap.hpp"

constexpr size_t GameMap::WIDTH;
constexpr size_t GameMap::HEIGHT;

int GameMap::getMapPosition(int x, int y) const {
    return _map[y][x];
}

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

            if (cell_type == ENEMY_SPAWN || cell_type == PLAYER_SPAWN)
                _spawns[cell_type].push_back(std::make_tuple(x, y));
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

            if (cell == PLAYER_SPAWN || cell == ENEMY_SPAWN)
                _spawns[cell].push_back(std::make_tuple(x, y));
        }
    }
}

positions_t const &GameMap::getPlayerSpawns() const {
    return _spawns.at(PLAYER_SPAWN);
}

positions_t const &GameMap::getEnemySpawns() const {
    return _spawns.at(ENEMY_SPAWN);
}
