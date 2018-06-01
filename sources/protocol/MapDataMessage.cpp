//
// Created by romain on 01/06/18.
//

#include "MapDataMessage.h"

constexpr int32_t MapDataMessage::PROTOCOL_ID;

void MapDataMessage::serialize(NetworkDataWriter &writer) const {
    std::string toString(_data);
    writer.writeUtf(toString);
}

void MapDataMessage::deserialize(NetworkDataReader &reader) {
    std::string data = reader.readUtf();
    _data = data.c_str();
    _length = data.size();
}

std::ostream &MapDataMessage::toString(std::ostream &o) const {
    return NetworkMessage::toString(o);
}

char const *MapDataMessage::getData() const {
    return _data;
}

size_t MapDataMessage::getLength() const {
    return _length;
}
