#pragma once

#include "enemy.hpp"

class Game;

class Blob : public Enemy {
public:
    Blob(Vector2 position, Game& ctx);

    void update(const InputSnapshot& input, float dt) override;
    void take_damage(float amount) override;
    void draw() const;
};