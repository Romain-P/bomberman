//
// Created by Mardel on 31/05/18.
//

#ifndef CPP_INDIE_STUDIO_BOMB_HPP
#define CPP_INDIE_STUDIO_BOMB_HPP

#include "GameObject.hpp"
#include "Player.hpp"

class Bomb : public GameObject
{
public:
    Bomb(Player &player, GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    virtual void Start();
    void Update() override;
    void LateUpdate();
    virtual void Destroy() = 0;
    void ExplodeLine(int x, int y);
protected:
    Player &_player;
    virtual void Explode() = 0;
    float _countDown;
    static constexpr float _explosionTime = 3;
};

class SoloBomb : public Bomb
{
public:
    SoloBomb(Player &player, GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Destroy();
    void Start();
private:
    irr::scene::IMeshSceneNode *_node;
    void Explode();
};

#endif //CPP_INDIE_STUDIO_BOMB_HPP
