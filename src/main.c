#include <raylib.h>
#include <raymath.h>
#include "consts.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/projectile.h"
#include "common.h"

RenderTexture2D game_screen;

void track_player(Camera2D* camera, Player* p, float dt) {
    // Vector2 Vector2Lerp(Vector2 v1, Vector2 v2, float amount)             
    camera->target = Vector2Lerp(camera->target, p->entity.position, 6.0f * dt);
}

int main(void)
{
    Player p = {
        .entity = (Entity) {
            .active = true,
            .position = (Vector2){100, 100},
            .size = (Vector2){30, 30},
            .velocity = (Vector2){0, 0}
        },
        .facing = RIGHT,
        .hp = 100,
        .id = AKSU,
        .accel = PLAYER_ACCEL,
        .decel = PLAYER_DECEL,
        .max_velocity = (Vector2) {PLAYER_WALK_SPEED, MAX_FALL_SPEED},
        .jump_force = PLAYER_JUMP_FORCE,
        .is_grounded = false,
        .buffer_timer = 0
    };

    Camera2D camera;
    Rectangle platforms[2] = {
        (Rectangle){120.0f, 280.0f, 140.0f, 16.0f},
        (Rectangle){340.0f, 220.0f, 160.0f, 16.0f}
    };

    camera.target = p.entity.position;
    camera.offset = (Vector2){GAME_SCREEN_WIDTH / 2.0f, GAME_SCREEN_HEIGHT / 2.0f};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AP4");
    
    game_screen = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        update_player(&p, dt, platforms, 2);
        track_player(&camera, &p, dt);
        BeginTextureMode(game_screen);
        BeginMode2D(camera);
        ClearBackground(BLACK);
        DrawText("AP4 Prototype", 20, 20, 30, WHITE);
        DrawRectangle(0, GAME_SCREEN_HEIGHT, GAME_SCREEN_WIDTH, 100, BLUE);
        DrawRectangleRec(platforms[0], GRAY);
        DrawRectangleRec(platforms[1], GRAY);
        DrawRectangle(p.entity.position.x, p.entity.position.y, p.entity.size.x, p.entity.size.y, PURPLE);
        
        EndMode2D();
        EndTextureMode();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(game_screen.texture, (Rectangle){0, 0, (float)game_screen.texture.width,
             -(float)game_screen.texture.height}, (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
