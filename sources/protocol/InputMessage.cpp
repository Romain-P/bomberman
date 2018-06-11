//
// Created by romain on 11/06/18.
//

#include "InputMessage.h"

void InputMessage::serialize(BinaryDataWriter &writer) const {
    writer.writeUint(_playerSessionId);
    writer.writeUint(_type);
}

void InputMessage::deserialize(BinaryDataReader &reader) {
    _playerSessionId = reader.readUint();
    _type = static_cast<InputType>(reader.readUint());
}

std::ostream &InputMessage::toString(std::ostream &o) const {
    std::string type;
    switch(_type) {
        case RIGHT:
            type = "right";
            break;
        case LEFT:
            type = "left";
            break;
        case FORWARD:
            type = "forward";
            break;
        case BACKWARD:
            type = "backward";
            break;
        case BOMB:
            type = "bomb";
            break;
        default:
            type = "undefined";
            break;
    }
    return o << "InputMessage(type=" << type << ")";
}

InputMessage::InputType InputMessage::getType() const {
    return _type;
}

size_t InputMessage::getPlayerId() const {
    return _playerSessionId;
}
