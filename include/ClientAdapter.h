//
// Created by romain on 30/05/18.
//

#ifndef CPP_INDIE_STUDIO_SIMPLECLIENTADAPTER_H
#define CPP_INDIE_STUDIO_SIMPLECLIENTADAPTER_H


#include <shared/ANetworkClientAdapter.h>

class ClientAdapter: public ANetworkClientAdapter {
public:

    ClientAdapter(size_t readSize, INetworkClientHandler *clientHandler)
            : ANetworkClientAdapter(readSize, clientHandler) {}

    void onDataReceived(NetworkClient *client, char const *buffer, size_t length) override;
    std::unique_ptr<ANetworkBuffer> bufferFactory() override;

private:

};


#endif //CPP_INDIE_STUDIO_SIMPLECLIENTADAPTER_H
