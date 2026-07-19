#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "entities/entity.h"
#include "common.h"

typedef enum {
    GHOST,
    FLAME,
    GOOP
} EnemyType;

typedef struct {
    Entity entity;
    float hp;
    EnemyType type;
    float behavior_timer;
    Direction facing;
} Enemy;


#endif // ENEMY_H