#include <raylib.h>

int main(void)
{
    InitWindow(1280, 720, "AP4");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("AP4 C bootstrap", 20, 20, 30, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
