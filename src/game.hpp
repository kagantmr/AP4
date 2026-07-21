#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <raylib.h>
#include "entities/player.hpp"

// Owns the window, render target, camera and world state, and drives the
// simulate/render loop.
class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void update(float dt);
    void render();
    void track_player(float dt);

    Player player;
    Camera2D camera{};
    RenderTexture2D game_screen{};
    std::array<Rectangle, 2> platforms{{
        Rectangle{120.0f, 280.0f, 140.0f, 16.0f},
        Rectangle{340.0f, 220.0f, 160.0f, 16.0f}
    }};
};

#endif // GAME_HPP
