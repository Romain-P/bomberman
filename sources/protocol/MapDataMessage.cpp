//
// Created by romain on 01/06/18.
//

#include "MapDataMessage.h"

constexpr int32_t MapDataMessage::PROTOCOL_ID;

void MapDataMessage::serialize(BinaryDataWriter &writer) const {
    writer.writeByteList(_data);
}

void MapDataMessage::deserialize(BinaryDataReader &reader) {
    _data = reader.readBytes();
}

std::ostream &MapDataMessage::toString(std::ostream &o) const {
    return o << "MapDataMessage(data.size()=" << _data.size() << ")";
}

std::vector<char> &MapDataMessage::getData() {
    return _data;
}