//
// Created by romain on 01/06/18.
//

#include "GameDataMessage.h"

void GameDataMessage::serialize(BinaryDataWriter &writer) const {
    writer.writeUint(_informations.size());

    for (auto &infos: _informations) {
        writer.writeUint(infos.clientId);
        writer.writeUint(infos.x);
        writer.writeUint(infos.y);
    }

    _map.serialize(writer);
}

void GameDataMessage::deserialize(BinaryDataReader &reader) {
    size_t size = reader.readUint();

    for (size_t i = 0; i < size; ++i) {
        PlayerInformation info;

        info.clientId = reader.readUint();
        info.x = reader.readUint();
        info.y = reader.readUint();

        _informations.push_back(info);
    }
    _map.deserialize(reader);
}

std::ostream &GameDataMessage::toString(std::ostream &o) const {
    o << "GameDataMessage(mapData=[...], players={ ";
    for (auto &info: _informations)
        o << "[id: " << info.clientId << ", posx: " << info.x << ", posy: " << info.y << "] ";
    return o << "})";
}

GameMap &GameDataMessage::getMap() {
    return _map;
}

std::vector<GameDataMessage::PlayerInformation> &GameDataMessage::getPlayerInformations() {
    return _informations;
}