//
// Created by romain on 31/05/18.
//

#include <HelloConnectMessage.h>
#include <GameDataMessage.h>
#include <LobbyUpdateMessage.h>
#include <iostream>
#include "NetworkProtocol.h"
#include "NetworkMessage.h"
#include "RequestStartGameMessage.h"
#include "InputMessage.h"

constexpr size_t NetworkProtocol::HEADER_INT_BYTES;
constexpr size_t NetworkProtocol::PACKET_MAX_SIZE;

const std::unordered_map<int32_t, std::unique_ptr<NetworkMessage>(*)()> NetworkProtocol::messages {
        { HelloConnectMessage::PROTOCOL_ID, packet_factory<HelloConnectMessage> },
        { GameDataMessage::PROTOCOL_ID, packet_factory<GameDataMessage> },
        { LobbyUpdateMessage::PROTOCOL_ID, packet_factory<LobbyUpdateMessage> },
        { RequestStartGameMessage::PROTOCOL_ID, packet_factory<RequestStartGameMessage> },
        { InputMessage::PROTOCOL_ID, packet_factory<InputMessage> }
};

template<typename T>
std::unique_ptr<NetworkMessage> NetworkProtocol::packet_factory() {
    return std::make_unique<T>();
}

size_t NetworkProtocol::packet_length(char const *buffer, size_t length) {
    if (length < HEADER_INT_BYTES)
        return (0);

    int32_t packet_size;
    memcpy(&packet_size, buffer, HEADER_INT_BYTES);
    return static_cast<size_t>(packet_size);
}

std::unique_ptr<NetworkMessage> NetworkProtocol::deserialize(BinaryDataReader &reader) {
    int32_t msg_id = reader.readInt();
    try {
        std::unique_ptr<NetworkMessage> message(messages.at(msg_id)());
        message->deserialize(reader);
        return message;
    } catch (std::exception &e) {
        throw std::runtime_error("NetworkProtocol::deserialize: can't build packet: unknown protocol id");
    }
}

void NetworkProtocol::serialize(NetworkMessage const &msg, BinaryDataWriter &writer) {
    BinaryDataWriter packetWriter(PACKET_MAX_SIZE);
    packetWriter.writeInt(msg.getProtocolId());
    msg.serialize(packetWriter);

    auto packet_length = static_cast<int32_t>(packetWriter.getSize());
    writer.writeInt(packet_length);
    writer.append(packetWriter.getBytes(), packetWriter.getSize());
}