#include "entities/projectile.h"
#include "common.h"
#include "consts.h"


void spawn_projectile(Projectile *arr, Vector2 spawn_pos, Direction facing, float damage) {
    for (int i = 0; i < MAX_PROJS; i++) {
        if (!arr[i].entity.active) {
            arr[i].spawn_pos = spawn_pos;
            arr[i].entity.position = spawn_pos;
            arr[i].facing = facing;
            arr[i].entity.velocity = facing == RIGHT ? (Vector2){PROJ_SPEED, 0} : (Vector2){-PROJ_SPEED, 0};
            arr[i].damage = damage;
            arr[i].entity.active = true;
            arr[i].is_player = true;
            break;
        }
    }
}

void update_projectile(Projectile* arr) {
    for (int i = 0; i < MAX_PROJS; i++) {
        if (arr[i].entity.active) {
            arr[i].entity.position.x += arr[i].entity.velocity.x;
            arr[i].entity.position.y += arr[i].entity.velocity.y;
        }
    }
}