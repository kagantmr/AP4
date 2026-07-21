#include "entities/player.hpp"
#include "consts.hpp"
#include <raylib.h>
#include <cmath>

Player::Player()
    : Entity(Vector2{100, 100}, Vector2{30, 30}) {
    active = true;
    facing = RIGHT;
    hp = 100;
    id = AKSU;
    accel = PLAYER_ACCEL;
    decel = PLAYER_DECEL;
    max_velocity = Vector2{PLAYER_WALK_SPEED, MAX_FALL_SPEED};
    jump_force = PLAYER_JUMP_FORCE;
    is_grounded = false;
    buffer_timer = 0;
}

void Player::update(float dt, const Rectangle *platforms, int platform_count) {
    float previous_y = position.y;

    // add gravity
    velocity.y += GRAVITY * dt;

    // clamp fall speed
    if (velocity.y > MAX_FALL_SPEED) {
        velocity.y = MAX_FALL_SPEED;
    }

    // update position
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    was_grounded = is_grounded;
    is_grounded = false;

    if (velocity.y >= 0.0f) {
        float prev_bottom = previous_y + size.y;
        float curr_bottom = position.y + size.y;
        float player_left = position.x;
        float player_right = position.x + size.x;

        for (int i = 0; i < platform_count; i++) {
            float plat_left = platforms[i].x;
            float plat_right = platforms[i].x + platforms[i].width;

            bool overlaps_x = (player_right > plat_left) && (player_left < plat_right);
            bool crossed_top = (prev_bottom <= platforms[i].y) && (curr_bottom >= platforms[i].y);

            if (overlaps_x && crossed_top) {
                is_grounded = true;
                velocity.y = 0.0f;
                position.y = platforms[i].y - size.y;
                break;
            }
        }

        if (!is_grounded && position.y + size.y > GAME_SCREEN_HEIGHT) {
            is_grounded = true;
            velocity.y = 0.0f;
            position.y = GAME_SCREEN_HEIGHT - size.y;
        }
    }

    if (is_grounded && buffer_timer > 0.0f) {
        velocity.y = -jump_force;
        buffer_timer = 0.0f;
        is_grounded = false;
    }

    float input_x = 0.0f;
    if (IsKeyDown(KEY_RIGHT)) input_x += 1.0f;
    if (IsKeyDown(KEY_LEFT)) input_x -= 1.0f;

    if (input_x > 0.0f) facing = RIGHT;
    if (input_x < 0.0f) facing = LEFT;

    float target_vx = input_x * max_velocity.x;
    float accel_rate = is_grounded ? accel : accel * AIR_CONTROL_FACTOR;
    float decel_rate = is_grounded ? decel : decel * AIR_CONTROL_FACTOR;
    float move_rate = (std::fabs(target_vx) > 0.0f) ? accel_rate : decel_rate;

    if (velocity.x < target_vx) {
        velocity.x = std::fmin(target_vx, velocity.x + move_rate * dt);
    } else if (velocity.x > target_vx) {
        velocity.x = std::fmax(target_vx, velocity.x - move_rate * dt);
    }

    if (std::fabs(velocity.x) < STOP_EPSILON) {
        velocity.x = 0.0f;
    }

    if (IsKeyPressed(KEY_Z)) {
        if ((is_grounded || coyote_timer > 0 || buffer_timer > 0)) {
            velocity.y = -jump_force;
        } else {
            buffer_timer = JUMP_BUFFER_TIME;
        }
    }

    if (IsKeyReleased(KEY_Z) && !is_grounded && velocity.y < 0) {
        velocity.y *= VARIABLE_JUMP_HEIGHT;
    }

    if (was_grounded && !is_grounded) {
        coyote_timer = COYOTE_TIME;
    }

    if (!is_grounded) {
        coyote_timer -= dt;
        buffer_timer -= dt;
    }
}

void Player::draw() const {
    DrawRectangleRec(bounds(), PURPLE);
}
