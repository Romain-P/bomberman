//
// Created by romain on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_DATAWRITER_H
#define CPP_INDIE_STUDIO_DATAWRITER_H


#include <shared/ANetworkBuffer.h>
#include <shared/BasicNetworkBuffer.h>

class DataWriter: public BasicNetworkBuffer {
    DataWriter(size_t maxSize): BasicNetworkBuffer(maxSize) {}
};


#endif //CPP_INDIE_STUDIO_DATAWRITER_H
