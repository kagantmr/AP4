#include "entities/projectile.hpp"
#include "common.hpp"
#include "consts.hpp"

void Projectile::update(const InputSnapshot &input, float dt) {
    (void)input;
    (void)dt;
    if (!active) return;
    position += velocity * dt;
    if (abs(position.x - spawn_pos.x) > MAX_TRAVEL_DIST) { active = false; }
    if (abs(position.y - spawn_pos.y) > MAX_TRAVEL_DIST) { active = false; }
}

void ProjectilePool::spawn(Vector2 spawn_pos, Direction facing, float damage) {
    for (Projectile &proj : projectiles) {
        if (proj.active) continue;
        proj.spawn_pos = spawn_pos;
        proj.position = spawn_pos;
        proj.facing = facing;
        proj.velocity = (facing == RIGHT) ? Vector2{PROJ_SPEED, 0}
                                          : Vector2{-PROJ_SPEED, 0};
        proj.size = (Vector2){15, 10};
        proj.damage = damage;
        proj.active = true;
        proj.is_player = true;
        break;
    }
}

void ProjectilePool::update(const InputSnapshot &input, float dt) {
    for (Projectile &proj : projectiles) {
        proj.update(input, dt);
    }
}

void ProjectilePool::draw() const {
    for (const Projectile &proj : projectiles) {
        if (!proj.active) continue;
        DrawRectangleRec(proj.bounds(), YELLOW);
    }
}

int ProjectilePool::getActiveCount() const {
    int count = 0;
    for (const Projectile &proj : projectiles) {
        if (proj.active) count++;
    }
    return count;
}