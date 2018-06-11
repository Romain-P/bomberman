//
// Created by romain on 10/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMELOBBYMESSAGE_H
#define CPP_INDIE_STUDIO_GAMELOBBYMESSAGE_H


#include <NetworkMessage.h>

class LobbyUpdateMessage: public NetworkMessage {
public:

    static constexpr int32_t PROTOCOL_ID = 3;

    LobbyUpdateMessage() : NetworkMessage(PROTOCOL_ID), _maxCount(), _readyCount() {}
    LobbyUpdateMessage(size_t readyCount, size_t maxCount) : NetworkMessage(PROTOCOL_ID), _maxCount(maxCount), _readyCount(readyCount){}

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;

    std::ostream &toString(std::ostream &o) const override;

    size_t getMaxPlayers() const;
    size_t getReadyPlayers() const;

private:

    size_t _maxCount;
    size_t _readyCount;
};


#endif //CPP_INDIE_STUDIO_GAMELOBBYMESSAGE_H
