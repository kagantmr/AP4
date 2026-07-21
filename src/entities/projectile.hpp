#pragma once

#include <array>
#include <raylib.h>
#include "entities/entity.hpp"
#include "common.hpp"
#include "consts.hpp"
#include "io/input.hpp"

class Projectile : public Entity {
public:
    Vector2 spawn_pos{0, 0};
    Direction facing{RIGHT};
    float damage{0};
    bool is_player{false};

    void update(const InputSnapshot &input, float dt) override;
};

// Fixed-size object pool that owns and recycles projectile instances.
class ProjectilePool {
public:
    std::array<Projectile, MAX_PROJS> projectiles{};

    void spawn(Vector2 spawn_pos, Direction facing, float damage);
    void update(const InputSnapshot &input, float dt);
    void draw() const;
    int getActiveCount() const;
};
