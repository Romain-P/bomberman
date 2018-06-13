//
// Created by romain on 11/06/18.
//

#include "InputMessage.h"

void InputMessage::serialize(BinaryDataWriter &writer) const {
    writer.writeUint(_playerSessionId);
    writer.writeUint((size_t)_type);
    writer.writeBool(_status);
}

void InputMessage::deserialize(BinaryDataReader &reader) {
    _playerSessionId = reader.readUint();
    _type = static_cast<PLAYERINPUT>(reader.readUint());
    _status = reader.readBool();
}

std::ostream &InputMessage::toString(std::ostream &o) const {
    std::string type;
    switch(_type) {
        case PLAYERINPUT::UP:
            type = "up";
            break;
        case PLAYERINPUT::DOWN:
            type = "down";
            break;
        case PLAYERINPUT::LEFT:
            type = "left";
            break;
        case PLAYERINPUT::RIGHT:
            type = "right";
            break;
        case PLAYERINPUT::PLACEBOMB:
            type = "bomb";
            break;
        default:
            type = "undefined";
            break;
    }
    return o << "InputMessage(type=" << type << ", sessionId=" << _playerSessionId << ")";
}

PLAYERINPUT InputMessage::getType() const {
    return _type;
}

bool InputMessage::getStatus() const {
    return _status;
}
size_t InputMessage::getPlayerId() const {
    return _playerSessionId;
}
