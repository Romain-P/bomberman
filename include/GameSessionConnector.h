//
// Created by romain on 02/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESESSIONCONNECTOR_H
#define CPP_INDIE_STUDIO_GAMESESSIONCONNECTOR_H

#include <GameSession.h>
#include <GameSessionHandler.h>
#include <NetworkClientAdapter.h>
#include <shared/ANetworkAsyncListener.h>

class GameSessionConnector: public NetworkAsyncListener {
public:

    GameSessionConnector() : _client(),
                             _session(),
                             _handler(),
                             _adapter(1024, &_handler)
    {}



    /**
     * Try to create a new game session instance
     *
     * @Return  true if the host exists
     */
    bool tryConnect(std::string const &ip, uint16_t gamePort);
    void pollEvent();
    GameSessionController &getController();
    void closeConnection();
    GameSessionController::State &getState();
protected:
    void onSocketNotified(socket_fd_t socket_id) override;
    void onListenerClosed(bool interrupted) override;
    socket_fd_t defineServerFd() override;
    GameSession *getSession();
private:
    std::unique_ptr<NetworkClient> _client;
    std::unique_ptr<GameSession> _session;
    GameSessionHandler _handler;
    NetworkClientAdapter _adapter;
};


#endif //CPP_INDIE_STUDIO_GAMESESSIONCONNECTOR_H
