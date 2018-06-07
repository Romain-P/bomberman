//
// Created by romain on 03/06/18.
//

#include <iostream>
#include "Test.h"

void Test::serialize(BinaryDataWriter &writer) const {
    writer.writeUint(_sizevar);
    writer.writeInt(_intvar);
    writer.writeUtf(_stringtest);
}

void Test::deserialize(BinaryDataReader &reader) {
    _sizevar = reader.readUint();
    _intvar = reader.readInt();
    _stringtest = reader.readUtf();
}

void Test::dump() {
    printf("size_t: %lu, int32: %d, string: %s\n", _sizevar, _intvar, _stringtest.c_str());
}
