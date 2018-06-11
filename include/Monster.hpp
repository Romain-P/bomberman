//
// Created by Mardel on 31/05/18.
//

#ifndef CPP_INDIE_STUDIO_MONSTER_HPP
#define CPP_INDIE_STUDIO_MONSTER_HPP

#include "GameObject.hpp"
#include "GameManager.hpp"

class Monster : public GameObject
{
public:
    Monster(GameManager &manager, vector2df position = vector2df(0, 0), vector2df rotation = vector2df(0, 0));
    void Start();
    void Update();
    void Destroy();
private:
    void CheckCollisions();
    bool IsValidPosition(vector2df pos);
    void ChangeDirection();
    vector2df _direction;
    irr::scene::IMeshSceneNode *_node;
    static constexpr int Speed = 1.5f;
    static const std::array<vector2df, 4> Directions;
};
#endif //CPP_INDIE_STUDIO_MONSTER_HPP
