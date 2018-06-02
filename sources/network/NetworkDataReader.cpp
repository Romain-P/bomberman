//
// Created by romain on 31/05/18.
//

#include <cstring>
#include "NetworkDataReader.h"

template<typename T>
void NetworkDataReader::readBytes(T &to_fill) {
    size_t size = sizeof(T);
    size_t pos = getPosition();

    memcpy(&to_fill, &_bytes[pos], size);
    setPosition(pos + size);
}

std::vector<char> NetworkDataReader::readBytes() {
    size_t count = readUint();
    size_t pos = getPosition();

    std::vector<char> read;

    for (int i = 0; i < count; i++)
        read.push_back(_bytes[pos + i]);
    setPosition(pos + count);
    return read;
}

bool NetworkDataReader::readBool() {
    uint8_t value;
    readBytes(value);
    return value;
}

int32_t NetworkDataReader::readInt() {
    int32_t value;
    readBytes(value);
    return value;
}

std::string NetworkDataReader::readUtf() {
    std::vector<char> read = readBytes();
    return std::string(read.begin(), read.end());
}

size_t NetworkDataReader::readUint() {
    size_t value;
    readBytes(value);
    return value;
}
