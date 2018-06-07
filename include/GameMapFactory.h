//
// Created by romain on 06/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMAPGENERATOR_H
#define CPP_INDIE_STUDIO_GAMEMAPGENERATOR_H


#include <GameMap.hpp>
#include <memory>
#include "GameDataSerializer.h"

class GameMapFactory {
public:
    explicit GameMapFactory(GameDataSerializer const &serializer) : _serializer(&serializer) {}

    static const std::string MAP_BASE_PATH;

    std::unique_ptr<GameMap> loadByTemplate(std::string const &file);
    std::unique_ptr<GameMap> loadByBinary(std::string const &file);
    std::unique_ptr<GameMap> generate(size_t players);

private:

    GameDataSerializer const *_serializer;
};


#endif //CPP_INDIE_STUDIO_GAMEMAPGENERATOR_H
