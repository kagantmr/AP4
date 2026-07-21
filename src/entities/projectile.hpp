#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <array>
#include <raylib.h>
#include "entities/entity.hpp"
#include "common.hpp"
#include "consts.hpp"

class Projectile : public Entity {
public:
    Vector2 spawn_pos{0, 0};
    Direction facing{RIGHT};
    float damage{0};
    bool is_player{false};

    void update(float dt) override;
};

// Fixed-size object pool that owns and recycles projectile instances.
class ProjectilePool {
public:
    std::array<Projectile, MAX_PROJS> projectiles{};

    void spawn(Vector2 spawn_pos, Direction facing, float damage);
    void update(float dt);
    void draw() const;
};

#endif // PROJECTILE_HPP
