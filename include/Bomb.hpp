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
    Bomb(int power, Player &player, GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Start();
    void Update() override;
    void Destroy();
    void ExplodeLine(int x, int y);
private:
    irr::scene::IMeshSceneNode *_node;
    Player &_player;
    void Explode();
    int _power;
    float _countDown;
    static constexpr float _explosionTime = 2;
};

#endif //CPP_INDIE_STUDIO_BOMB_HPP
