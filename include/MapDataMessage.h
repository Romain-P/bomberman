//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_MAPDATAMESSAGE_H
#define CPP_INDIE_STUDIO_MAPDATAMESSAGE_H


#include <cstdint>
#include "NetworkMessage.h"

class MapDataMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 2;

    MapDataMessage() : NetworkMessage(PROTOCOL_ID), _data(nullptr), _length() {}

    MapDataMessage(char const *data, size_t length) : NetworkMessage(PROTOCOL_ID), _data(data), _length(length) {}

    void serialize(NetworkDataWriter &writer) const override;
    void deserialize(NetworkDataReader &reader) override;

    char const *getData() const;
    size_t getLength() const;

    std::ostream &toString(std::ostream &o) const override;

private:

    char const *_data;
    size_t _length;
};


#endif //CPP_INDIE_STUDIO_MAPDATAMESSAGE_H
