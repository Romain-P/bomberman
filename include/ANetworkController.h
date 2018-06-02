//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKCONTROLLER_H
#define CPP_INDIE_STUDIO_NETWORKCONTROLLER_H

#include <sys/types.h>
#include <unordered_map>
#include <functional>
#include "NetworkMessage.h"
#include "ANetworkClient.h"

using handler_t = std::function<void (ANetworkClient *, NetworkMessage *)>;
using handlers_t = std::unordered_map<size_t, handler_t>;

template <typename T, typename V, typename X>
using typed_handler_t = void (T::*)(X *, V *);

class ANetworkController {
public:

    virtual void init();

    void parseMessage(ANetworkClient *client, NetworkMessage *msg);
protected:

    virtual void defineMessageHandlers(handlers_t &handlers) = 0;

    template <typename T,typename V,typename X>
    handler_t handler(T &holder, typed_handler_t<T, V, X> addr) {
        return [&holder, addr](ANetworkClient *client, NetworkMessage *msg) mutable {
            (holder.*addr)(dynamic_cast<X *>(client), dynamic_cast<V *>(msg));
        };
    };

private:

    handlers_t _handlers;
};


#endif //CPP_INDIE_STUDIO_NETWORKCONTROLLER_H
