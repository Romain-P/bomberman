//
// Created by romain on 03/06/18.
//

#include "GameDataSerializer.h"

void GameDataSerializer::load(std::string const &name, Serializable &serializable) {
    fillReader(name);
    serializable.deserialize(_reader);
}

void GameDataSerializer::save(std::string const &name, Serializable const &serializable) {
    std::ofstream file(name + ".bin", std::ios::out|std::ios::binary);

    _writer.clear();
    serializable.serialize(_writer);

    file.write(_writer.getBytes(), _writer.getSize());
    file.close();
}

void GameDataSerializer::fillReader(std::string const &name) {
    _reader.clear();

    std::ifstream file(name + ".bin", std::ios::in|std::ios::binary|std::ios::ate);
    if (!file.is_open())
        throw std::runtime_error("can't find the requested file name)");

    std::streampos size;
    size = file.tellg();

    auto *binaryData = new char[size];
    file.seekg (0, std::ios::beg);
    file.read (binaryData, size);
    file.close();

    _reader.append(binaryData, size);
    _reader.setPosition(0);

    delete[] binaryData;
}
