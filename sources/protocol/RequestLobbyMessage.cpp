//
// Created by romain on 11/06/18.
//

#include "RequestLobbyMessage.h"

void RequestLobbyMessage::serialize(BinaryDataWriter &writer) const {

}

void RequestLobbyMessage::deserialize(BinaryDataReader &reader) {

}

std::ostream &RequestLobbyMessage::toString(std::ostream &o) const {
    return o << "RequestLobbyMessage()";
}
