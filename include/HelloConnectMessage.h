//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_HELLOCONNECTMESSAGE_H
#define CPP_INDIE_STUDIO_HELLOCONNECTMESSAGE_H

#include <NetworkMessage.h>

class HelloConnectMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 1;

    HelloConnectMessage() : NetworkMessage(PROTOCOL_ID) {}

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;

    std::ostream &toString(std::ostream &o) const override;
};


#endif //CPP_INDIE_STUDIO_HELLOCONNECTMESSAGE_H
