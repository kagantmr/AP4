#pragma once

#include <raylib.h>
#include "entities/entity.hpp"
#include "common.hpp"
#include "io/input.hpp"

enum CharType {
    AKSU,
    OYA,
    PINAR,
    YESIM
};

class Game; // fwd declare

class Player : public Entity {
public:
    int hp{100};
    Direction facing{RIGHT};
    CharType id{AKSU};
    float accel{0};
    float decel{0};
    Vector2 maxVelocity{0, 0};
    bool isGrounded{false};
    bool wasGrounded{false};
    float jumpForce{0};
    float coyoteTimer{0};
    float bufferTimer{0};
    float shootCooldown{0};
    float shootBufferTimer{0};

    Player(Game & gameContext);

    // Points the player at the world geometry it should collide against. The
    // caller retains ownership; the data must outlive the player.
    void setPlatforms(const Rectangle *data, int count);

    // Advances physics, resolves platform collisions and applies input.
    void update(const InputSnapshot &input, float dt) override;

    void draw() const;

private:
    const Rectangle *platforms{nullptr};
    Game& gameCtx;
    int platform_count{0};
};
