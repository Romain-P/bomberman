//
// Created by romain on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_DATAWRITER_H
#define CPP_INDIE_STUDIO_DATAWRITER_H


#include <shared/ANetworkBuffer.h>
#include <shared/BasicNetworkBuffer.h>
#include <string>
#include "NetworkProtocol.h"

class BinaryDataWriter: public BasicNetworkBuffer {
public:

    explicit BinaryDataWriter(size_t maxSize): BasicNetworkBuffer(maxSize) {}

    BinaryDataWriter() : BasicNetworkBuffer(NetworkProtocol::PACKET_MAX_SIZE) {}

    template<typename T>
    void writeBytes(T &to_copy);

    void writeByteList(std::vector<char> const &to_copy);
    void writeBool(bool value);
    void writeInt(int32_t value);
    void writeUint(size_t value);
    void writeUtf(std::string str);

};


#endif //CPP_INDIE_STUDIO_DATAWRITER_H
