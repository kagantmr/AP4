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

class Player : public Entity {
public:
    int hp{100};
    Direction facing{RIGHT};
    CharType id{AKSU};
    float accel{0};
    float decel{0};
    Vector2 max_velocity{0, 0};
    bool is_grounded{false};
    bool was_grounded{false};
    float jump_force{0};
    float coyote_timer{0};
    float buffer_timer{0};

    Player();

    // Points the player at the world geometry it should collide against. The
    // caller retains ownership; the data must outlive the player.
    void set_platforms(const Rectangle *data, int count);

    // Advances physics, resolves platform collisions and applies input.
    void update(const InputSnapshot &input, float dt) override;

    void draw() const;

private:
    const Rectangle *platforms{nullptr};
    int platform_count{0};
};
