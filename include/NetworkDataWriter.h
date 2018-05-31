//
// Created by romain on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_DATAWRITER_H
#define CPP_INDIE_STUDIO_DATAWRITER_H


#include <shared/ANetworkBuffer.h>
#include <shared/BasicNetworkBuffer.h>
#include <string>

class NetworkDataWriter: public BasicNetworkBuffer {
public:

    NetworkDataWriter(size_t maxSize): BasicNetworkBuffer(maxSize) {}

    template<typename T>
    void writeBytes(T &to_copy);

    template<typename T>
    void writeBytes(std::vector<T> &to_copy);

    void writeBool(bool value);
    void writeInt(int32_t value);
    void writeUtf(std::string str);

};


#endif //CPP_INDIE_STUDIO_DATAWRITER_H
