//
// Created by romain on 11/06/18.
//

#ifndef CPP_INDIE_STUDIO_INPUTMESSAGE_H
#define CPP_INDIE_STUDIO_INPUTMESSAGE_H

#include "NetworkMessage.h"

class InputMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 6;

    enum InputType {
        RIGHT = 0,
        LEFT,
        FORWARD,
        BACKWARD,
        BOMB
    };

    InputMessage() : NetworkMessage(PROTOCOL_ID), _playerSessionId(), _type() {}
    explicit InputMessage(InputType type, size_t playerId = 0) : NetworkMessage(PROTOCOL_ID), _playerSessionId(playerId), _type(type) {}

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;

    std::ostream &toString(std::ostream &o) const override;

    size_t getPlayerId() const;
    InputType getType() const;
private:

    size_t _playerSessionId;
    InputType _type;
};


#endif //CPP_INDIE_STUDIO_INPUTMESSAGE_H
