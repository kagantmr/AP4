#include "player.h"
#include "consts.h"
#include <stdio.h>
#include <raylib.h>
#include <math.h>

void update_player(Player *p, float dt, const Rectangle *platforms, int platform_count) {
    float previous_y = p->entity.position.y;

    // add gravity
    p->entity.velocity.y += GRAVITY * dt;
    
    // clamp fall speed
    if (p->entity.velocity.y > MAX_FALL_SPEED) {
        p->entity.velocity.y = MAX_FALL_SPEED;
    }
    
    // update position
    p->entity.position.x += p->entity.velocity.x * dt;
    p->entity.position.y += p->entity.velocity.y * dt;

    p->was_grounded = p->is_grounded;
    p->is_grounded = false;

    if (p->entity.velocity.y >= 0.0f) {
        float prev_bottom = previous_y + p->entity.size.y;
        float curr_bottom = p->entity.position.y + p->entity.size.y;
        float player_left = p->entity.position.x;
        float player_right = p->entity.position.x + p->entity.size.x;

        for (int i = 0; i < platform_count; i++) {
            float plat_left = platforms[i].x;
            float plat_right = platforms[i].x + platforms[i].width;

            bool overlaps_x = (player_right > plat_left) && (player_left < plat_right);
            bool crossed_top = (prev_bottom <= platforms[i].y) && (curr_bottom >= platforms[i].y);

            if (overlaps_x && crossed_top) {
                p->is_grounded = true;
                p->entity.velocity.y = 0.0f;
                p->entity.position.y = platforms[i].y - p->entity.size.y;
                break;
            }
        }

        if (!p->is_grounded && p->entity.position.y + p->entity.size.y > GAME_SCREEN_HEIGHT) {
            p->is_grounded = true;
            p->entity.velocity.y = 0.0f;
            p->entity.position.y = GAME_SCREEN_HEIGHT - p->entity.size.y;
        }
    }

    if (p->is_grounded && p->buffer_timer > 0.0f) {
        p->entity.velocity.y = -p->jump_force;
        p->buffer_timer = 0.0f;
        p->is_grounded = false;
    }

    float input_x = 0.0f;
    if (IsKeyDown(KEY_RIGHT)) input_x += 1.0f;
    if (IsKeyDown(KEY_LEFT)) input_x -= 1.0f;

    if (input_x > 0.0f) p->facing = RIGHT;
    if (input_x < 0.0f) p->facing = LEFT;

    float target_vx = input_x * p->max_velocity.x;
    float accel_rate = p->is_grounded ? p->accel : p->accel * AIR_CONTROL_FACTOR;
    float decel_rate = p->is_grounded ? p->decel : p->decel * AIR_CONTROL_FACTOR;
    float move_rate = (fabsf(target_vx) > 0.0f) ? accel_rate : decel_rate;

    if (p->entity.velocity.x < target_vx) {
        p->entity.velocity.x = fminf(target_vx, p->entity.velocity.x + move_rate * dt);
    } else if (p->entity.velocity.x > target_vx) {
        p->entity.velocity.x = fmaxf(target_vx, p->entity.velocity.x - move_rate * dt);
    }

    if (fabsf(p->entity.velocity.x) < STOP_EPSILON) {
        p->entity.velocity.x = 0.0f;
    }

    if (IsKeyPressed(KEY_Z)) {
        if ((p->is_grounded || p->coyote_timer > 0 || p->buffer_timer > 0)) {
            p->entity.velocity.y = -p->jump_force;
        } else {
            p->buffer_timer = JUMP_BUFFER_TIME;
        }
    } 

    if (IsKeyReleased(KEY_Z) && !p->is_grounded && p->entity.velocity.y < 0) {
        p->entity.velocity.y *= VARIABLE_JUMP_HEIGHT;
    }


    if (p->was_grounded && !p->is_grounded) {
        p->coyote_timer = COYOTE_TIME;
    }

    if (!p->is_grounded) {
        p->coyote_timer -= dt;
        p->buffer_timer -= dt;
    }


} 