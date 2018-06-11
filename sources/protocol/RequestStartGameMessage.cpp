//
// Created by romain on 11/06/18.
//

#include "RequestStartGameMessage.h"

void RequestStartGameMessage::serialize(BinaryDataWriter &writer) const {
}

void RequestStartGameMessage::deserialize(BinaryDataReader &reader) {
}

std::ostream &RequestStartGameMessage::toString(std::ostream &o) const {
    return o << "RequestStartGameMessage()";
}
