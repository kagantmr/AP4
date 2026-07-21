#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "entities/entity.hpp"
#include "common.hpp"

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

    // Advances physics, resolves platform collisions and handles input.
    void update(float dt, const Rectangle *platforms, int platform_count);

    void draw() const;
};

#endif // PLAYER_H
