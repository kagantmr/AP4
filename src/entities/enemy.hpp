#pragma once

#include <raylib.h>
#include "entities/entity.hpp"
#include "common.hpp"
#include "io/input.hpp"

enum EnemyType {
    GHOST,
    FLAME,
    GOOP
};

class Enemy : public Entity {
public:
    float hp{0};
    const float max_hp;
    bool is_dead;
    EnemyType type{GHOST};
    float behavior_timer{0};
    Direction facing{RIGHT};

    Enemy(Vector2 pos, Vector2 sz, float max_hp) 
        : Entity(pos, sz), max_hp(max_hp), hp(max_hp) {}

    // Enemies run on their own AI and ignore the player's input snapshot.
    virtual void update(const InputSnapshot& input, float dt) = 0;
    virtual void take_damage(float amount) = 0;
};
