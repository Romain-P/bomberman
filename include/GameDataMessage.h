//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_MAPDATAMESSAGE_H
#define CPP_INDIE_STUDIO_MAPDATAMESSAGE_H


#include <cstdint>
#include "NetworkMessage.h"
#include "GameMap.hpp"

class GameDataMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 2;

    struct PlayerInformation {
        size_t clientId;
        float x;
        float y;
    };

    GameDataMessage() : NetworkMessage(PROTOCOL_ID), _map() {}

    explicit GameDataMessage(GameMap &map, std::vector<PlayerInformation> const &infos) :
            NetworkMessage(PROTOCOL_ID),
            _map(GameMap(map.getData(), map.getCompletionTime(), map.getEnemyCount())),
            _informations(infos)
    {}

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;

    GameMap &getMap();
    std::vector<PlayerInformation> &getPlayerInformations();

    std::ostream &toString(std::ostream &o) const override;

private:

    GameMap _map;
    std::vector<PlayerInformation> _informations;
};


#endif //CPP_INDIE_STUDIO_MAPDATAMESSAGE_H
