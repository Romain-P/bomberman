//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKCLIENTHANDLER_H
#define CPP_INDIE_STUDIO_NETWORKCLIENTHANDLER_H

#include <sys/types.h>

class NetworkClient;

class INetworkClientHandler {
public:

    virtual ~INetworkClientHandler() = default;

    virtual void onConnect(NetworkClient *client) = 0;
    virtual void onReceive(NetworkClient *client, char const *buffer, size_t length) = 0;
    virtual void onSent(NetworkClient *client, char const *buffer, size_t length) = 0;
    virtual void onDisconnect(NetworkClient *client) = 0;

};


#endif //CPP_INDIE_STUDIO_NETWORKCLIENTHANDLER_H
