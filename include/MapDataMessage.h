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

    MapDataMessage() : NetworkMessage(PROTOCOL_ID), _data() {}

    MapDataMessage(std::vector<char> const &data) : NetworkMessage(PROTOCOL_ID), _data(data) {}

    void serialize(NetworkDataWriter &writer) const override;
    void deserialize(NetworkDataReader &reader) override;

    std::vector<char> &getData();

    std::ostream &toString(std::ostream &o) const override;

private:

    std::vector<char> _data;
};


#endif //CPP_INDIE_STUDIO_MAPDATAMESSAGE_H
