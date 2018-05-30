//
// Created by romain on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_BASICNETWORKBUFFER_H
#define CPP_INDIE_STUDIO_BASICNETWORKBUFFER_H


#include <shared/ANetworkBuffer.h>
#include <vector>

class BasicNetworkBuffer: public ANetworkBuffer {
public:

    BasicNetworkBuffer(size_t maxSize) : ANetworkBuffer(maxSize), _bytes() {};

    bool append(char *bytes, size_t length) override;
    void clear() override;
    char *getBytes() override;

private:

    std::vector<char> _bytes;
};


#endif //CPP_INDIE_STUDIO_BASICNETWORKBUFFER_H
