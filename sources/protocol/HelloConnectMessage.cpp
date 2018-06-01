//
// Created by romain on 01/06/18.
//

#include "HelloConnectMessage.h"

constexpr int32_t HelloConnectMessage::PROTOCOL_ID;

void HelloConnectMessage::serialize(NetworkDataWriter &writer) const {

}

void HelloConnectMessage::deserialize(NetworkDataReader &reader) {

}

std::ostream &HelloConnectMessage::toString(std::ostream &o) const {
    return o << "HelloConnectMessage()";
}
