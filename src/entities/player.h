#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "entities/entity.h"
#include "common.h"

typedef enum {
    AKSU,
    OYA,
    PINAR,
    YESIM
} CharType;

typedef struct {
    Entity entity;
    int hp;
    Direction facing;
    CharType id;
    float accel, decel;
    Vector2 max_velocity;
    bool is_grounded, was_grounded;
    float jump_force;
    float coyote_timer;
    float buffer_timer;
} Player;

void update_player(Player *p, float dt, const Rectangle *platforms, int platform_count);

#endif // PLAYER_H