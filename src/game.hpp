#pragma once

#include <vector>  // <--- Add this
#include <raylib.h>
#include "entities/player.hpp"
#include "entities/blob.hpp"
#include "entities/projectile.hpp"
#include "io/input.hpp"

// Owns the window, render target, camera and world state, and drives the
// simulate/render loop.
class Game {
public:
    Game();
    ~Game();

    void run();
    void spawn_proj(Vector2 & pos, Direction facing);
    const std::vector<Rectangle>& getPlatforms() const { return platforms; }

private:
    void update(const InputSnapshot &input, float dt);
    void render();
    void track_player(float dt);

    Player player;
    Blob blob;
    ProjectilePool projPool;
    Camera2D camera{};
    RenderTexture2D game_screen{};
    std::vector<Rectangle> platforms{
        {120.0f, 280.0f, 140.0f, 16.0f},
        {340.0f, 220.0f, 160.0f, 16.0f}
    };
};
