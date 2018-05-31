//
// Created by romain on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_BASICNETWORKBUFFER_H
#define CPP_INDIE_STUDIO_BASICNETWORKBUFFER_H


#include <shared/ANetworkBuffer.h>
#include <vector>

class BasicNetworkBuffer: public ANetworkBuffer {

public:

    explicit BasicNetworkBuffer(size_t maxSize) : ANetworkBuffer(maxSize), _bytes() {};

    bool append(char *bytes, size_t length) override;
    bool drop(size_t from, size_t to) override;
    void clear() override;
    char *getBytes() override;
    void allocate(size_t nbytes) override;
    void resize(size_t nbytes) override;
    size_t getSize() const override;

protected:

    std::vector<char> _bytes;
};


#endif //CPP_INDIE_STUDIO_BASICNETWORKBUFFER_H
