//
// Created by romain on 06/06/18.
//

#include "GameMapFactory.h"
#include <fstream>
#include <unistd.h>

const std::string GameMapFactory::MAP_BASE_PATH = std::string("resources/maps/");

std::unique_ptr<GameMap> GameMapFactory::loadByTemplate(std::string const &file) {
    int data[GameMap::HEIGHT][GameMap::WIDTH];
    std::string path = MAP_BASE_PATH + file;
    size_t time;
    size_t enemies;

    if (access(path.c_str(), F_OK) == -1) {
        std::cerr << "cant find file: " << path << std::endl;
        throw std::runtime_error("GameMapFactory::loadByTemplate: file not found");
    }
    std::ifstream infile(path);
    std::string line;
    for (ssize_t i = -2; getline(infile, line); ++i) {
        if (i == -2)
            time = atoi(line.c_str());
        else if (i == -1)
            enemies = atoi(line.c_str());
        else if (line.size() != GameMap::WIDTH || i >= (int)GameMap::HEIGHT) {
            std::cerr << "invalid map size. file: " << path << " line: " << (i + 3) << " length: " << line.size()
                      <<  " expected: " << GameMap::HEIGHT << std::endl;
            error:
            throw std::runtime_error("GameMapFactory::loadByTemplate: invalid map data");
        } else {
            for (pos_x x = 0; x < GameMap::WIDTH; ++x) {
                int cell_type = line.c_str()[x] - '0';
                if (cell_type < 0 || cell_type > 4) {
                    std::cerr << "invalid cell type. type_id: " << cell_type << std::endl;
                    goto error;
                }
                data[i][x] = cell_type;
            }
        }
    }

    infile.close();
    return std::make_unique<GameMap>(data, time, enemies);
}

std::unique_ptr<GameMap> GameMapFactory::generate(size_t players) {
    int data[GameMap::HEIGHT][GameMap::WIDTH] = { GameMap::NONE };



    return std::make_unique<GameMap>(data, 0);
}

std::unique_ptr<GameMap> GameMapFactory::loadByBinary(std::string const &file) {
    return std::unique_ptr<GameMap>();
}
