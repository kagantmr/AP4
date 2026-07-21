#include "entities/player.hpp"
#include "consts.hpp"
#include "game.hpp"
#include <raylib.h>
#include <cmath>

Player::Player(Game & gameContext)
    : Entity(Vector2{100, 100}, Vector2{30, 45}), gameCtx(gameContext) {
    active = true;
    facing = RIGHT;
    hp = 100;
    id = AKSU;
    accel = PLAYER_ACCEL;
    decel = PLAYER_DECEL;
    maxVelocity = Vector2{PLAYER_WALK_SPEED, MAX_FALL_SPEED};
    jumpForce = PLAYER_JUMP_FORCE;
    isGrounded = false;
    bufferTimer = 0;
}

void Player::update(const InputSnapshot &input, float dt) {
    float previous_y = position.y;

    // add gravity
    velocity.y += GRAVITY * dt;

    // clamp fall speed
    if (velocity.y > MAX_FALL_SPEED) {
        velocity.y = MAX_FALL_SPEED;
    }

    // update position
    position += velocity * dt;

    wasGrounded = isGrounded;
    isGrounded = false;

    if (velocity.y >= 0.0f) {
        float prev_bottom = previous_y + size.y;
        float curr_bottom = position.y + size.y;
        float player_left = position.x;
        float player_right = position.x + size.x;

        for (int i = 0; i < gameCtx.getPlatforms().size(); i++) {
            float plat_left = gameCtx.getPlatforms()[i].x;
            float plat_right = gameCtx.getPlatforms()[i].x + gameCtx.getPlatforms()[i].width;

            bool overlaps_x = (player_right > plat_left) && (player_left < plat_right);
            bool crossed_top = (prev_bottom <= gameCtx.getPlatforms()[i].y) && (curr_bottom >= gameCtx.getPlatforms()[i].y);

            if (overlaps_x && crossed_top) {
                isGrounded = true;
                velocity.y = 0.0f;
                position.y = gameCtx.getPlatforms()[i].y - size.y;
                break;
            }
        }

        if (!isGrounded && position.y + size.y > GAME_SCREEN_HEIGHT) {
            isGrounded = true;
            velocity.y = 0.0f;
            position.y = GAME_SCREEN_HEIGHT - size.y;
        }
    }

    if (isGrounded && bufferTimer > 0.0f) {
        velocity.y = -jumpForce;
        bufferTimer = 0.0f;
        isGrounded = false;
    }

    float input_x = 0.0f;
    if (input.MoveRight) input_x += 1.0f;
    if (input.MoveLeft) input_x -= 1.0f;

    if (input_x > 0.0f) facing = RIGHT;
    if (input_x < 0.0f) facing = LEFT;

    float target_vx = input_x * maxVelocity.x;
    float accel_rate = isGrounded ? accel : accel * AIR_CONTROL_FACTOR;
    float decel_rate = isGrounded ? decel : decel * AIR_CONTROL_FACTOR;
    float move_rate = (std::fabs(target_vx) > 0.0f) ? accel_rate : decel_rate;

    if (velocity.x < target_vx) {
        velocity.x = std::fmin(target_vx, velocity.x + move_rate * dt);
    } else if (velocity.x > target_vx) {
        velocity.x = std::fmax(target_vx, velocity.x - move_rate * dt);
    }

    if (std::fabs(velocity.x) < STOP_EPSILON) {
        velocity.x = 0.0f;
    }

    if (input.JumpPressed) {
        if ((isGrounded || coyoteTimer > 0 || bufferTimer > 0)) {
            velocity.y = -jumpForce;
        } else {
            bufferTimer = JUMP_BUFFER_TIME;
        }
    }

    if (input.JumpReleased && !isGrounded && velocity.y < 0) {
        velocity.y *= VARIABLE_JUMP_HEIGHT;
    }

    if (wasGrounded && !isGrounded) {
        coyoteTimer = COYOTE_TIME;
    }

    if (!isGrounded) {
        coyoteTimer -= dt;
        bufferTimer -= dt;
    }

    shootCooldown -= dt;
    shootBufferTimer -= dt;

    if (input.ShootPressed) {
        shootBufferTimer = PLAYER_SHOOT_BUFFER;
    }

    if (shootBufferTimer > 0) {
        if (shootCooldown <= 0) {
            Vector2 pos = (facing == LEFT) ? (Vector2){position.x - 35, position.y + 22.5f} : (Vector2){position.x + 35, position.y + 22.5f};
            gameCtx.spawn_proj(pos, facing);
            shootCooldown = PLAYER_SHOOT_COOLDOWN_MAX;
            shootBufferTimer = 0;
        }
    }
}

void Player::draw() const {
    char health[4];
    snprintf(health, sizeof(health), "%d", hp);
    health[3] = '\0';
    DrawText(health, position.x, position.y - 30, 20, WHITE);
    DrawRectangleRec(bounds(), PURPLE);
}
