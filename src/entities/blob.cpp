#include "blob.hpp"
#include "game.hpp"
#include "consts.hpp"

Blob::Blob(Vector2 spawn_pos, Game& ctx) 
    : Enemy(spawn_pos, {20.0f, 20.0f}, 50.0f, ctx) // Or pass parameters up if Enemy has a constructor
{
    this->position = spawn_pos;
    this->size = (Vector2){20.0f, 20.0f};
    this->hp = 50.0f;
    this->active = true;   // <--- Ensure it is active
    this->is_dead = false; // <--- Ensure it is alive
}

void Blob::update(const InputSnapshot &input, float dt) {
    (void)input;

    if (is_dead || !active) return;

    // 1. Apply gravity
    velocity.y += GRAVITY * dt;

    // Set horizontal speed based on current facing direction (assuming facing is stored or tracked)
    float speed = 50.0f;
    velocity.x = (facing == RIGHT) ? speed : -speed;

    // 2. Move horizontally
    position.x += velocity.x * dt;

    // 3. Move vertically and check floor collisions
    position.y += velocity.y * dt;

    Rectangle blob_rect = { position.x, position.y, size.x, size.y };
    bool grounded = false;

    for (const auto& platform : gameCtx.getPlatforms()) {
        if (CheckCollisionRecs(blob_rect, platform)) {
            if (velocity.y > 0.0f) {
                position.y = platform.y - size.y;
                velocity.y = 0.0f;
                blob_rect.y = position.y;
                grounded = true;
            }
        }
    }

    // 4. Edge Detection (only check if it's currently standing on a platform)
    if (grounded) {
        // Look ahead slightly in the direction of movement
        float look_ahead_x = (facing == RIGHT) ? (position.x + size.x + 2.0f) : (position.x - 2.0f);
        float check_y = position.y + size.y + 2.0f; // Just below its feet

        bool found_floor_ahead = false;
        for (const auto& platform : gameCtx.getPlatforms()) {
            // Check if a platform exists right under the edge ahead
            if (look_ahead_x >= platform.x && look_ahead_x <= (platform.x + platform.width) &&
                check_y >= platform.y && check_y <= (platform.y + platform.height)) {
                found_floor_ahead = true;
                break;
            }
        }

        // If there's no floor ahead, turn around!
        if (!found_floor_ahead) {
            facing = (facing == RIGHT) ? LEFT : RIGHT;
        }
    }
}

void Blob::take_damage(float amount) {
    if (is_dead || !active) return;

    hp -= amount;
    if (hp <= 0.0f) {
        hp = 0.0f;
        is_dead = true;
        active = false; // Deactivate so it stops rendering and updating
    }
}

void Blob::draw() const {
    if (is_dead || !active) return;
    char hp_text[16];
    snprintf(hp_text, sizeof(hp_text), "%.0f", hp);
    DrawText(hp_text, static_cast<int>(position.x), static_cast<int>(position.y - 50), 20, WHITE);
    DrawEllipse(static_cast<int>(position.x), static_cast<int>(position.y), 
                  static_cast<int>(size.x), static_cast<int>(size.y), RED);
}