//
// Created by romain on 03/06/18.
//

#ifndef CPP_INDIE_STUDIO_TEST_H
#define CPP_INDIE_STUDIO_TEST_H


#include <Serializable.h>

class Test: public Serializable {
public:

    void serialize(BinaryDataWriter &writer) const override;
    void deserialize(BinaryDataReader &reader) override;
    void dump();

private:
    size_t _sizevar = 19921;
    int _intvar = 27;
    std::string _stringtest = "ouloulou c beau";
};


#endif //CPP_INDIE_STUDIO_TEST_H
