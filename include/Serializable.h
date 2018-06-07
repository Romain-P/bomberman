//
// Created by romain on 03/06/18.
//

#ifndef CPP_INDIE_STUDIO_SERIALIZABLE_H
#define CPP_INDIE_STUDIO_SERIALIZABLE_H


#include "BinaryDataWriter.h"
#include "BinaryDataReader.h"

class Serializable {
public:

    virtual void serialize(BinaryDataWriter &writer) const = 0;
    virtual void deserialize(BinaryDataReader &reader) = 0;

};


#endif //CPP_INDIE_STUDIO_SERIALIZABLE_H
