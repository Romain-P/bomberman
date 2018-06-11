//
// Created by romain on 11/06/18.
//

#ifndef CPP_INDIE_STUDIO_REQUESTLOBBYMESSAGE_H
#define CPP_INDIE_STUDIO_REQUESTLOBBYMESSAGE_H

#include <NetworkMessage.h>

class RequestLobbyMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 5;

    RequestLobbyMessage() : NetworkMessage(PROTOCOL_ID) {}

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;

    std::ostream &toString(std::ostream &o) const override;
};


#endif //CPP_INDIE_STUDIO_REQUESTLOBBYMESSAGE_H
