//
// Created by romain on 03/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEDATASERIALIZER_H
#define CPP_INDIE_STUDIO_GAMEDATASERIALIZER_H


#include <string>
#include "Serializable.h"
#include <iostream>
#include <fstream>

class GameDataSerializer {
public:

    void save(std::string const &name, Serializable const &serializable);
    void load(std::string const &name, Serializable &serializable);

    template<typename T>
    inline std::unique_ptr<T> load(std::string const &name) {
        static_assert(std::is_base_of<Serializable, T>::value);

        fillReader(name);

        auto loaded = std::make_unique<T>();
        loaded->deserialize(_reader);
        return loaded;
    }

private:

    BinaryDataReader _reader;
    BinaryDataWriter _writer;

    void fillReader(std::string const &name);
};


#endif //CPP_INDIE_STUDIO_GAMEDATASERIALIZER_H
