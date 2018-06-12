//
// Created by romain on 11/06/18.
//

#ifndef CPP_INDIE_STUDIO_INPUTMESSAGE_H
#define CPP_INDIE_STUDIO_INPUTMESSAGE_H

#include "NetworkMessage.h"
#include "Player.hpp"

class InputMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 6;

    InputMessage() : NetworkMessage(PROTOCOL_ID), _playerSessionId(), _type(), _status() {}
    explicit InputMessage(PLAYERINPUT type, bool status, size_t playerId = 0) : NetworkMessage(PROTOCOL_ID), _playerSessionId(playerId), _type(type),  _status(status) {}

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;

    std::ostream &toString(std::ostream &o) const override;

    size_t getPlayerId() const;
    PLAYERINPUT getType() const;
    bool getStatus() const;
private:
    size_t _playerSessionId;
    PLAYERINPUT _type;
    bool _status;
};


#endif //CPP_INDIE_STUDIO_INPUTMESSAGE_H
