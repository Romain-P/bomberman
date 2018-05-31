//
// Created by romain on 31/05/18.
//

#include "NetworkProtocol.h"

constexpr size_t NetworkProtocol::HEADER_INT_BYTES;
constexpr size_t NetworkProtocol::PACKET_MAX_SIZE;

const std::unordered_map<int32_t, std::unique_ptr<NetworkMessage>(*)()> NetworkProtocol::messages {
    //TODO: add protocol messages
};

template<typename T>
std::unique_ptr<NetworkMessage> NetworkProtocol::packet_factory() {
    return std::unique_ptr<NetworkMessage>();
}

int32_t NetworkProtocol::packet_length(char const *buffer) {
    int32_t length;
    memcpy(&length, buffer, HEADER_INT_BYTES);
    return length;
}

std::unique_ptr<NetworkMessage> NetworkProtocol::deserialize(NetworkDataReader &reader) {
    int32_t msg_id = reader.readInt();
    try {
        std::unique_ptr<NetworkMessage> message(messages.at(msg_id)());
        message->deserialize(reader);
        return message;
    } catch (std::exception &e) {
        throw std::runtime_error("NetworkProtocol::deserialize: can't build packet: unknown protocol id");
    }
}

void NetworkProtocol::serialize(NetworkMessage const &msg, NetworkDataWriter &writer) {
    NetworkDataWriter packetWriter(PACKET_MAX_SIZE);
    packetWriter.writeInt(msg.getProtocolId());
    msg.serialize(packetWriter);

    auto packet_length = static_cast<int32_t>(packetWriter.getSize());
    writer.writeInt(packet_length);
    writer.append(packetWriter.getBytes(), packetWriter.getSize());
}