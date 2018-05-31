//
// Created by romain on 31/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKPROTOCOL_H
#define CPP_INDIE_STUDIO_NETWORKPROTOCOL_H


#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include "NetworkMessage.h"

class NetworkProtocol {
public:

    static constexpr size_t PACKET_MAX_SIZE = 4096;
    static constexpr size_t HEADER_INT_BYTES = sizeof(int32_t);

    template<typename T>
    static std::unique_ptr<NetworkMessage> packet_factory();

    static int32_t packet_length(char const *buffer);
    static std::unique_ptr<NetworkMessage> deserialize(NetworkDataReader &reader);
    static void serialize(NetworkMessage const &msg, NetworkDataWriter &writer);

private:
    static const std::unordered_map<int32_t, std::unique_ptr<NetworkMessage>(*)()> messages;
};


#endif //CPP_INDIE_STUDIO_NETWORKPROTOCOL_H
