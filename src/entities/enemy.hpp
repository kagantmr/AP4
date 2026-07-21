#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
#include "entities/entity.hpp"
#include "common.hpp"

enum EnemyType {
    GHOST,
    FLAME,
    GOOP
};

class Enemy : public Entity {
public:
    float hp{0};
    EnemyType type{GHOST};
    float behavior_timer{0};
    Direction facing{RIGHT};
};

#endif // ENEMY_HPP
