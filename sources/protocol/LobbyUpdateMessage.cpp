//
// Created by romain on 10/06/18.
//

#include "LobbyUpdateMessage.h"

void LobbyUpdateMessage::serialize(BinaryDataWriter &writer) const {
    writer.writeUint(_readyCount);
    writer.writeUint(_maxCount);
}

void LobbyUpdateMessage::deserialize(BinaryDataReader &reader) {
    _readyCount = reader.readUint();
    _maxCount = reader.readUint();
}

std::ostream &LobbyUpdateMessage::toString(std::ostream &o) const {
    return o << "LobbyUpdateMessage(readyCount=" << _readyCount << ", maxCount=" << _maxCount << ")";
}

size_t LobbyUpdateMessage::getMaxPlayers() const {
    return _maxCount;
}

size_t LobbyUpdateMessage::getReadyPlayers() const {
    return _readyCount;
}
