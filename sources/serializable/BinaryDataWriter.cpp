//
// Created by romain on 30/05/18.
//

#include "BinaryDataWriter.h"

template<typename T>
void BinaryDataWriter::writeBytes(T &to_copy) {
    size_t size = sizeof(T);
    ssize_t pos = getPosition();

    if (pos + size > _bytes.size())
        resize(pos + size);
    memcpy(&_bytes[pos], &to_copy, size);
    setPosition(pos + size);
}

void BinaryDataWriter::writeByteList(std::vector<char> const &to_copy) {
    size_t size = to_copy.size();

    writeUint(size);
    size_t pos = getPosition();

    if (pos + size > _bytes.size())
        resize(pos + size);
    memcpy(&_bytes[pos], &to_copy[0], static_cast<size_t>(size));
    setPosition(size + pos);
}

void BinaryDataWriter::writeBool(bool value) {
    auto rval = static_cast<uint8_t>(value);
    writeBytes(rval);
}

void BinaryDataWriter::writeInt(int32_t value) {
    writeBytes(value);
}

void BinaryDataWriter::writeUtf(std::string str) {
    std::vector<char> asList(str.begin(), str.end());
    writeByteList(asList);
}

void BinaryDataWriter::writeUint(size_t value) {
    writeBytes(value);
}
