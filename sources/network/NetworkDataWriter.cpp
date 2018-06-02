//
// Created by romain on 30/05/18.
//

#include "NetworkDataWriter.h"

template<typename T>
void NetworkDataWriter::writeBytes(T &to_copy) {
    size_t size = sizeof(T);
    ssize_t pos = getPosition();

    if (pos + size > _bytes.size())
        resize(pos + size);
    memcpy(&_bytes[pos], &to_copy, size);
    setPosition(pos + size);
}

void NetworkDataWriter::writeByteList(std::vector<char> const &to_copy) {
    size_t size = to_copy.size();

    writeUint(size);
    size_t pos = getPosition();

    if (pos + size > _bytes.size())
        resize(pos + size);
    memcpy(&_bytes[pos], &to_copy[0], static_cast<size_t>(size));
    setPosition(size + pos);
}

void NetworkDataWriter::writeBool(bool value) {
    auto rval = static_cast<uint8_t>(value);
    writeBytes(rval);
}

void NetworkDataWriter::writeInt(int32_t value) {
    writeBytes(value);
}

void NetworkDataWriter::writeUtf(std::string str) {
    std::vector<char> asList(str.begin(), str.end());
    writeBytes(asList);
}

void NetworkDataWriter::writeUint(size_t value) {
    writeBytes(value);
}
