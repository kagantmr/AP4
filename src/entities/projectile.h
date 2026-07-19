#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>
#include "entities/entity.h"
#include "common.h"
#include <stdbool.h>

typedef struct {
    Entity entity;
    Vector2 spawn_pos;
    Direction facing;
    float damage;
    bool is_player;
} Projectile;


void spawn_projectile(Projectile *arr, Vector2 spawn_pos, Direction facing, float damage);

#endif