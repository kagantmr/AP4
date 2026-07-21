#include "game.hpp"
#include "consts.hpp"
#include <raymath.h>

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AP4");
    game_screen = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    SetTargetFPS(60);

    camera.target = player.position;
    camera.offset = Vector2{GAME_SCREEN_WIDTH / 2.0f, GAME_SCREEN_HEIGHT / 2.0f};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
}

Game::~Game() {
    UnloadRenderTexture(game_screen);
    CloseWindow();
}

void Game::track_player(float dt) {
    camera.target = Vector2Lerp(camera.target, player.position, 6.0f * dt);
}

void Game::update(float dt) {
    player.update(dt, platforms.data(), static_cast<int>(platforms.size()));
    track_player(dt);
}

void Game::render() {
    BeginTextureMode(game_screen);
    BeginMode2D(camera);
    ClearBackground(BLACK);
    DrawText("AP4 Prototype", 20, 20, 30, WHITE);
    DrawRectangle(0, GAME_SCREEN_HEIGHT, GAME_SCREEN_WIDTH, 100, BLUE);
    for (const Rectangle &platform : platforms) {
        DrawRectangleRec(platform, GRAY);
    }
    player.draw();
    EndMode2D();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(
        game_screen.texture,
        Rectangle{0, 0, static_cast<float>(game_screen.texture.width),
                  -static_cast<float>(game_screen.texture.height)},
        Rectangle{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
        Vector2{0, 0}, 0.0f, WHITE);
    EndDrawing();
}

void Game::run() {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        update(dt);
        render();
    }
}
