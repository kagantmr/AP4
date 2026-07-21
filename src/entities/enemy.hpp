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
    EnemyType type{GHOST};
    float behavior_timer{0};
    Direction facing{RIGHT};

    // Enemies run on their own AI and ignore the player's input snapshot.
    void update(const InputSnapshot &input, float dt) override {
        (void)input;
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
    }
};
