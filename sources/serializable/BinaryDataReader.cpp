//
// Created by romain on 31/05/18.
//

#include <cstring>
#include "BinaryDataReader.h"

template<typename T>
void BinaryDataReader::readBytes(T &to_fill) {
    size_t size = sizeof(T);
    size_t pos = getPosition();

    memcpy(&to_fill, &_bytes[pos], size);
    setPosition(pos + size);
}

std::vector<char> BinaryDataReader::readBytes() {
    size_t count = readUint();
    size_t pos = getPosition();

    std::vector<char> read;

    for (size_t i = 0; i < count; i++)
        read.push_back(_bytes[pos + i]);
    setPosition(pos + count);
    return read;
}

bool BinaryDataReader::readBool() {
    uint8_t value;
    readBytes(value);
    return value;
}

int32_t BinaryDataReader::readInt() {
    int32_t value;
    readBytes(value);
    return value;
}

std::string BinaryDataReader::readUtf() {
    std::vector<char> read = readBytes();
    return std::string(read.begin(), read.end());
}

size_t BinaryDataReader::readUint() {
    size_t value;
    readBytes(value);
    return value;
}
