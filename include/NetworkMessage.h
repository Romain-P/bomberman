//
// Created by romain on 31/05/18.
//

#ifndef CPP_INDIE_STUDIO_NETWORKMESSAGE_H
#define CPP_INDIE_STUDIO_NETWORKMESSAGE_H


#include <cstdint>
#include <ostream>
#include "NetworkDataWriter.h"
#include "NetworkDataReader.h"

class NetworkMessage {
public:
    virtual ~NetworkMessage() = default;
    explicit NetworkMessage(int32_t protocol_id) : _protocolId(protocol_id) {};

    virtual void serialize(NetworkDataWriter &writer) const = 0;
    virtual void deserialize(NetworkDataReader &reader) = 0;

    inline virtual std::ostream& toString(std::ostream& o) const {
        return o << "NetworkMessage(id=" << _protocolId << ")";
    }

    inline int32_t getProtocolId() const {
        return _protocolId;
    }

private:
    int32_t _protocolId;
};

inline std::ostream &operator<<(std::ostream &o, const NetworkMessage &msg) {
    return msg.toString(o);
}


#endif //CPP_INDIE_STUDIO_NETWORKMESSAGE_H
